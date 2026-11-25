#!/usr/bin/env python3
#
# Copyright (C) 2026 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
"""Merge and visualize Level Zero fabric topology checker logs.

The validation layer's fabric topology checker
(ZEL_ENABLE_FABRIC_TOPOLOGY_CHECKER=1, ZEL_FABRIC_TOPOLOGY_OUTPUT=<dir>) writes one
JSON Lines file per process. This tool merges the files from any number of
processes and hosts, joins IPC exports to imports so cross-process traffic is
attributed to the exporting device, and produces:

  * a text summary on stdout (topology, per-link traffic, process pairs), and
  * optionally a self-contained HTML report (--html) with the topology graph,
    traffic arcs, a throughput timeline with a time scrubber, and tables.

Examples:
  fabric_topology_viewer.py /shared/ftc                     # text summary
  fabric_topology_viewer.py /shared/ftc --html report.html  # + HTML report
  fabric_topology_viewer.py /shared/ftc --html report.html --watch 2
      # regenerate every 2 s while the workload runs; the page reloads itself

Only the Python standard library is used.
"""

import argparse
import glob
import json
import os
import sys
import time
from collections import defaultdict

CATEGORIES = [
    ("h2d", "Host to device"),
    ("d2h", "Device to host"),
    ("peer", "Device to device"),
    ("ipc", "Cross-process (IPC)"),
    ("local", "On-device"),
]


def fmt_bytes(n):
    n = float(n)
    for unit in ("B", "KiB", "MiB", "GiB", "TiB"):
        if abs(n) < 1024 or unit == "TiB":
            return ("%d %s" % (n, unit)) if unit == "B" else ("%.1f %s" % (n, unit))
        n /= 1024.0
    return "%.1f TiB" % n


def collect_files(paths):
    files = []
    for p in paths:
        if os.path.isdir(p):
            files.extend(sorted(glob.glob(os.path.join(p, "*.jsonl"))))
        else:
            files.extend(sorted(glob.glob(p)))
    return files


def read_records(files):
    records = []
    for f in files:
        try:
            with open(f, "r", encoding="utf-8", errors="replace") as fh:
                for line in fh:
                    line = line.strip()
                    if not line:
                        continue
                    try:
                        records.append(json.loads(line))
                    except ValueError:
                        # The last line of a live file may be partially written.
                        continue
        except OSError as e:
            print("warning: cannot read %s: %s" % (f, e), file=sys.stderr)
    return records


class Model:
    """Merged view of all process streams."""

    def __init__(self, records):
        self.processes = {}  # pkey -> info
        self.nodes = {}  # node id -> info
        self.fabric_edges = {}  # (edge uuid, vertex a, vertex b) -> info
        self.vertices = {}  # fabric vertex id -> properties (+ "node" when it is a device)
        self.fabric_queries = {}  # (host, driver) -> latest "fabric_query" diagnostics
        self.p2p = {}  # (a, b) -> info
        self.vertex_node = {}  # fabric vertex uuid -> node id
        self.exports_by_hash = {}
        self.exports_by_ino = {}
        self.imports = {}  # (pkey, import_id) -> record
        self.traffic = []  # (pkey, record)
        self.api_totals = defaultdict(lambda: [0, 0])  # (pkey, exec, src, dst, op) -> [bytes, ops]
        self._build(records)

    # -- helpers -------------------------------------------------------------
    @staticmethod
    def pkey(r):
        return "%s:%s" % (r.get("host", "?"), r.get("pid", "?"))

    def host_node(self, host):
        nid = host + "|host"
        if nid not in self.nodes:
            self.nodes[nid] = {"id": nid, "host": host, "kind": "host", "label": "Host memory"}
        return nid

    def device_node(self, host, loc):
        nid = host + "|" + loc
        if nid not in self.nodes:
            self.nodes[nid] = {"id": nid, "host": host, "kind": "device", "label": loc[4:16], "sub": False}
        return nid

    def proc(self, r):
        k = self.pkey(r)
        if k not in self.processes:
            self.processes[k] = {
                "key": k, "host": r.get("host", "?"), "pid": r.get("pid"), "exe": "", "env": {},
                "start_us": r.get("ts_us"), "end_us": None, "devices": set(), "ended": False,
            }
        return self.processes[k]

    # -- build ---------------------------------------------------------------
    def _build(self, records):
        for r in records:
            t = r.get("type")
            host = r.get("host", "?")
            p = self.proc(r)
            ts = r.get("ts_us")
            if ts is not None:
                p["start_us"] = min(p["start_us"] or ts, ts)
                p["end_us"] = max(p["end_us"] or ts, ts)
            if t == "process_start":
                p["interval_ms"] = r.get("interval_ms")
                p["exe"] = r.get("exe", "")
                p["env"] = r.get("env", {})
            elif t == "process_end":
                p["ended"] = True
            elif t == "device":
                nid = self.device_node(host, r["id"])
                n = self.nodes[nid]
                n.update({
                    "name": r.get("name", ""), "uuid": r.get("uuid", ""), "pci": r.get("pci", ""),
                    "sub": bool(r.get("sub")), "sub_id": r.get("sub_id"), "dev_type": r.get("dev_type", ""),
                })
                if r.get("root"):
                    n["root"] = self.device_node(host, r["root"])
                # PCI address identifies the card; the tile index the sub-device.
                ident = r.get("pci") or r["id"][4:12]
                n["label"] = ident + (" tile %s" % r.get("sub_id") if r.get("sub") else "")
            elif t == "topology":
                self.host_node(host)
                if r.get("fabric_query"):
                    self.fabric_queries[(host, r.get("driver"))] = r["fabric_query"]
                for loc in r.get("devices", []):
                    self.device_node(host, loc)
                for e in r.get("p2p", []):
                    a, b = self.device_node(host, e["a"]), self.device_node(host, e["b"])
                    self.p2p[(a, b)] = dict(e, a=a, b=b)
                for v in r.get("fabric_vertices", []):
                    rec = dict(v, host=host)
                    if v.get("device") and not v.get("remote"):
                        rec["node"] = self.device_node(host, v["device"])
                    known = self.vertices.get(v["id"])
                    # A vertex seen as local by its own host beats the remote view of it.
                    if known is None or (known.get("remote") and not v.get("remote")):
                        self.vertices[v["id"]] = rec
                for e in r.get("fabric_edges", []):
                    self.fabric_edges.setdefault((e.get("id"), e["a"], e["b"]), dict(e, host=host))
            elif t == "ipc_export":
                rec = dict(r, pkey=self.pkey(r))
                if r.get("handle_hash"):
                    self.exports_by_hash.setdefault((host, r["handle_hash"]), rec)
                if r.get("dmabuf_ino"):
                    self.exports_by_ino.setdefault((host, r["dmabuf_ino"]), rec)
            elif t == "ipc_import":
                self.imports[(self.pkey(r), r.get("import_id"))] = r
            elif t == "traffic":
                self.traffic.append((self.pkey(r), r))
                for e in r.get("edges", []):
                    if e.get("exec", "").startswith("dev:"):
                        p["devices"].add(self.device_node(host, e["exec"]))
                    tot = self.api_totals[(self.pkey(r), e.get("exec"), e.get("src"), e.get("dst"), e.get("op"))]
                    tot[0] += e.get("bytes", 0)
                    tot[1] += e.get("ops", 0)

        # Every fabric vertex becomes a node: devices map onto their device node,
        # switches and unresolved remote vertices get nodes of their own.
        for vid, v in self.vertices.items():
            node = v.get("node")
            if node is None:
                kind = "switch" if v.get("type") == "switch" else "remote"
                node = "%s|%s" % (kind, vid)
                self.nodes.setdefault(node, {
                    "id": node, "host": "fabric", "kind": kind, "home": v.get("host"),
                    "label": ("switch " if kind == "switch" else "remote ") + (v.get("pci") or vid[:8]),
                })
                v["node"] = node
            self.vertex_node[vid] = node
            self.nodes[node]["vertex"] = {k: v.get(k) for k in ("id", "uuid", "type", "remote", "pci")}
            self.nodes[node]["vertex"]["reported_by"] = v.get("host")

        def card_of(nid):
            n = self.nodes.get(nid, {})
            return n.get("root") if n.get("sub") else nid

        resolved = {}
        for (eid, a, b), e in self.fabric_edges.items():
            na, nb = self.vertex_node.get(a), self.vertex_node.get(b)
            if not na or not nb or na == nb:
                continue
            key = (eid,) + tuple(sorted((na, nb)))
            resolved.setdefault(key, dict(e, a=key[1], b=key[2], va=a, vb=b,
                                          intra=card_of(na) == card_of(nb)))
        self.fabric_links = list(resolved.values())
        self._assign_short_labels()

    def _assign_short_labels(self):
        """Labels devices "card.tile" per host, cards ordered by PCI address."""
        by_host = defaultdict(list)
        for n in self.nodes.values():
            if n["kind"] == "device" and not (n.get("sub") and n.get("root") in self.nodes):
                by_host[n["host"]].append(n)
        for host, roots in by_host.items():
            roots.sort(key=lambda n: (n.get("pci") or "~", n.get("uuid") or n["id"]))
            for idx, root in enumerate(roots):
                root["card"] = idx
                root["short"] = str(idx)
        for n in self.nodes.values():
            if n["kind"] == "device" and n.get("sub") and n.get("root") in self.nodes:
                root = self.nodes[n["root"]]
                n["card"] = root.get("card")
                n["short"] = "%s.%s" % (root.get("card"), n.get("sub_id", "?"))
            elif n["kind"] == "host":
                n["short"] = "host"
            elif n["kind"] in ("switch", "remote"):
                n["short"] = "sw" if n["kind"] == "switch" else "rem"

    # -- IPC join ------------------------------------------------------------
    def resolve_import(self, pkey, import_id):
        """Returns (exporter record or None, join method)."""
        imp = self.imports.get((pkey, import_id))
        if imp is None:
            return None, "missing"
        host = imp.get("host")
        if imp.get("handle_hash") and (host, imp["handle_hash"]) in self.exports_by_hash:
            return self.exports_by_hash[(host, imp["handle_hash"])], "handle"
        if imp.get("dmabuf_ino") and (host, imp["dmabuf_ino"]) in self.exports_by_ino:
            return self.exports_by_ino[(host, imp["dmabuf_ino"])], "dmabuf"
        return None, "unresolved"

    def location_node(self, pkey, host, loc):
        """Maps a process-local location string to (node id, owner process key or None)."""
        if not loc:
            return None, None
        if loc == "host":
            return self.host_node(host), pkey
        if loc.startswith("dev:"):
            return self.device_node(host, loc), pkey
        if loc.startswith("ipc:"):
            try:
                import_id = int(loc[4:])
            except ValueError:
                return None, None
            exp, _ = self.resolve_import(pkey, import_id)
            if exp is not None:
                node, _ = self.location_node(exp["pkey"], exp["host"], exp.get("loc"))
                return node, exp["pkey"]
            imp = self.imports.get((pkey, import_id))
            if imp and imp.get("device", "").startswith("dev:"):
                return self.device_node(host, imp["device"]), None
            return self.host_node(host), None
        return None, None

    def ipc_links(self):
        links = []
        for (pkey, import_id), imp in sorted(self.imports.items(), key=lambda kv: str(kv[0])):
            exp, how = self.resolve_import(pkey, import_id)
            links.append({
                "importer": pkey,
                "importer_device": self.device_node(imp.get("host", "?"), imp["device"])
                if imp.get("device", "").startswith("dev:") else None,
                "exporter": exp["pkey"] if exp else None,
                "source": self.location_node(exp["pkey"], exp["host"], exp.get("loc"))[0] if exp else None,
                "size": (exp or {}).get("size") or imp.get("size", 0),
                "importer_host": imp.get("host"),
                "exporter_host": exp.get("host") if exp else None,
                "kind": imp.get("kind", "ipc"),
                "join": how,
            })
        return links

    # -- traffic -------------------------------------------------------------
    def flows(self):
        """Expands API-level edges into physical flows.

        A copy executed by device E reads from src and writes to dst. Data
        crosses a link src -> E when src != E, and E -> dst when dst != E.
        Yields (t_us, from_node, to_node, category, bytes, ops, pkey, peer_pkey).
        """
        for pkey, r in self.traffic:
            host = r.get("host", "?")
            t1 = r.get("t1_us") or r.get("ts_us")
            for e in r.get("edges", []):
                exec_node = self.device_node(host, e["exec"]) if e.get("exec", "").startswith("dev:") else None
                src_node, src_owner = self.location_node(pkey, host, e.get("src"))
                dst_node, dst_owner = self.location_node(pkey, host, e.get("dst"))
                nbytes, ops = e.get("bytes", 0), e.get("ops", 0)
                cross_src = str(e.get("src") or "").startswith("ipc:")
                cross_dst = str(e.get("dst") or "").startswith("ipc:")
                # The other process whose memory this transfer touches, if any.
                peer = next((o for o in (src_owner, dst_owner) if o and o != pkey), None)
                hops = []
                if src_node and exec_node and src_node != exec_node:
                    hops.append((src_node, exec_node, cross_src))
                if dst_node and exec_node and dst_node != exec_node:
                    hops.append((exec_node, dst_node, cross_dst))
                if not hops and exec_node:
                    yield (t1, exec_node, exec_node, "local", nbytes, ops, pkey, peer)
                    continue
                for a, b, cross in hops:
                    if cross:
                        cat = "ipc"
                    elif self.nodes[a]["kind"] == "host":
                        cat = "h2d"
                    elif self.nodes[b]["kind"] == "host":
                        cat = "d2h"
                    else:
                        cat = "peer"
                    yield (t1, a, b, cat, nbytes, ops, pkey, peer)

    def to_json(self, sources):
        flows = list(self.flows())
        times = [f[0] for f in flows if f[0]] + [p["start_us"] for p in self.processes.values() if p["start_us"]]
        t_min = min(times) if times else 0
        t_max = max(times + [p["end_us"] or 0 for p in self.processes.values()]) if times else 1
        span = max(t_max - t_min, 1)
        nbins = 120
        # Never narrower than the coarsest reporting interval, or the series turns into spikes.
        min_interval_us = max([1000.0] + [float(p.get("interval_ms") or 0) * 1000.0 for p in self.processes.values()])
        width = max(span / float(nbins), min_interval_us)
        nbins = int(span // width) + 1
        agg = defaultdict(lambda: [0, 0])
        for t, a, b, cat, nbytes, ops, pkey, peer in flows:
            bin_i = int(((t or t_min) - t_min) // width)
            v = agg[(bin_i, a, b, cat, pkey, peer or "")]
            v[0] += nbytes
            v[1] += ops
        flow_rows = [
            [k[0], k[1], k[2], k[3], k[4], k[5], v[0], v[1]] for k, v in sorted(agg.items(), key=lambda kv: kv[0])
        ]
        hosts = sorted({n["host"] for n in self.nodes.values() if n["host"] != "fabric"})
        procs = []
        for p in sorted(self.processes.values(), key=lambda p: p["key"]):
            env = p["env"] or {}
            rank = next((env[k] for k in ("RANK", "PMI_RANK", "PMIX_RANK", "OMPI_COMM_WORLD_RANK", "SLURM_PROCID")
                         if k in env), None)
            procs.append({
                "key": p["key"], "host": p["host"], "pid": p["pid"], "exe": p["exe"], "env": env, "rank": rank,
                "start_us": p["start_us"], "end_us": p["end_us"], "ended": p["ended"],
                "devices": sorted(p["devices"]),
            })
        return {
            "generated": time.strftime("%Y-%m-%d %H:%M:%S"),
            "sources": sources,
            "hosts": hosts,
            "nodes": sorted(self.nodes.values(), key=lambda n: (n["host"], n["kind"] != "host", n.get("root", n["id"]),
                                                                 n.get("sub", False), n["id"])),
            "fabric": self.fabric_links,
            "p2p": list(self.p2p.values()),
            "processes": procs,
            "ipc": self.ipc_links(),
            "bins": {"t0_us": t_min, "width_us": width, "n": nbins},
            "flows": flow_rows,
            "categories": [{"id": c, "label": l} for c, l in CATEGORIES],
        }


# -- text summary ---------------------------------------------------------------

def print_summary(model, data, top=25, out=sys.stdout):
    nodes = {n["id"]: n for n in data["nodes"]}

    def label(nid):
        n = nodes.get(nid)
        if not n:
            return nid or "-"
        if n["kind"] == "device":
            return "%s:%s [%s]" % (n["host"], n.get("short", "?"), n.get("label", nid))
        return "%s:%s" % (n["host"], n.get("label", nid))

    print("Fabric topology summary (%d process stream(s))" % len(data["processes"]), file=out)
    print("=" * 72, file=out)
    for host in data["hosts"]:
        print("\nHost %s" % host, file=out)
        for n in data["nodes"]:
            if n["host"] != host or n["kind"] != "device":
                continue
            indent = "    " if n.get("sub") else "  "
            print("%s%-5s %-22s %s  uuid=%s" % (indent, n.get("short", "?"), n.get("label"), n.get("name", ""),
                                                 n.get("uuid", "?")), file=out)
    if data["fabric"]:
        print("\nFabric links", file=out)
        for e in data["fabric"]:
            print("  %s <-> %s  %-7s bw=%s %s  lat=%s %s  %s-duplex" % (
                label(e["a"]), label(e["b"]), e.get("model", ""), e.get("bandwidth"), e.get("bw_unit"),
                e.get("latency"), e.get("lat_unit"), e.get("duplexity")), file=out)
    else:
        print("\nFabric links: none", file=out)
        for (host, driver), q in sorted(model.fabric_queries.items(), key=lambda kv: str(kv[0])):
            if not q.get("vertex_table"):
                why = "fabric vertex DDI table not available to the validation layer"
            elif q.get("vertex_result") not in ("0x0", None):
                why = "zeFabricVertexGetExp returned %s" % q.get("vertex_result")
            elif not q.get("vertices"):
                why = "driver reported no fabric vertices"
            elif not q.get("edge_table"):
                why = "fabric edge DDI table not available to the validation layer"
            elif q.get("edges") == 0:
                why = "driver reported no edges between %d vertex pair(s)" % q.get("edge_pairs", 0)
            else:
                why = "edges reported but could not be mapped to devices"
            print("  %s driver %s: %s (vertices=%s, subvertices=%s, edges=%s, edge_errors=%s, duplicate_uuids=%s)" % (
                host, driver, why, q.get("vertices"), q.get("subvertices"), q.get("edges"), q.get("edge_errors"),
                q.get("duplicate_vertex_uuids")), file=out)
        if not model.fabric_queries:
            print("  (streams predate fabric diagnostics; re-run with the current validation layer)", file=out)
    p2p_ok = [e for e in data["p2p"] if e.get("access")]
    if data["p2p"]:
        print("\nP2P access: %d of %d device pairs" % (len(p2p_ok), len(data["p2p"])), file=out)

    print("\nProcesses", file=out)
    for p in data["processes"]:
        print("  %s rank=%s exe=%s%s" % (p["key"], p["rank"] if p["rank"] is not None else "-",
                                         os.path.basename(p["exe"] or "?"), "" if p["ended"] else "  (running)"),
              file=out)

    link_tot = defaultdict(lambda: [0, 0])
    pair_tot = defaultdict(int)
    for row in data["flows"]:
        _, a, b, cat, pkey, peer, nbytes, ops = row
        link_tot[(a, b, cat)][0] += nbytes
        link_tot[(a, b, cat)][1] += ops
        if peer:
            pair_tot[tuple(sorted((pkey, peer)))] += nbytes
    print("\nData movement by link", file=out)
    if not link_tot:
        print("  (no copies or fills recorded)", file=out)
    ranked = sorted(link_tot.items(), key=lambda kv: -kv[1][0])
    if top and len(ranked) > top:
        print("  (top %d of %d links; use --top 0 for all)" % (top, len(ranked)), file=out)
        ranked = ranked[:top]
    for (a, b, cat), (nbytes, ops) in ranked:
        arrow = "(on device)" if a == b else "-> %s" % label(b)
        print("  %-12s %s %s  %s in %d op(s)" % (cat, label(a), arrow, fmt_bytes(nbytes), ops), file=out)
    if data["ipc"]:
        print("\nIPC sharing", file=out)
        for l in data["ipc"]:
            print("  %s imports %s from %s  [%s, join=%s]" % (
                l["importer"], fmt_bytes(l["size"] or 0), l["exporter"] or "?", l["kind"], l["join"]), file=out)
    if pair_tot:
        print("\nProcess pairs exchanging data", file=out)
        for (p1, p2), nbytes in sorted(pair_tot.items(), key=lambda kv: -kv[1]):
            print("  %s <-> %s  %s" % (p1, p2, fmt_bytes(nbytes)), file=out)


# -- HTML report ----------------------------------------------------------------

HTML_TEMPLATE = r"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
__REFRESH__
<title>Level Zero fabric topology</title>
<style>
.viz-root {
  color-scheme: light;
  --page: #f9f9f7; --surface-1: #fcfcfb;
  --text-primary: #0b0b0b; --text-secondary: #52514e; --muted: #898781;
  --grid: #e1e0d9; --axis: #c3c2b7; --border: rgba(11,11,11,0.10);
  --series-1: #2a78d6; --series-2: #eb6834; --series-3: #1baf7a; --series-4: #eda100; --series-5: #e87ba4;
  --link: #c3c2b7;
}
@media (prefers-color-scheme: dark) {
  :root:where(:not([data-theme="light"])) .viz-root {
    color-scheme: dark;
    --page: #0d0d0d; --surface-1: #1a1a19;
    --text-primary: #f0efec; --text-secondary: #c3c2b7; --muted: #898781;
    --grid: #2c2c2a; --axis: #383835; --border: rgba(255,255,255,0.10);
    --series-1: #3987e5; --series-2: #d95926; --series-3: #199e70; --series-4: #c98500; --series-5: #d55181;
    --link: #52514e;
  }
}
:root[data-theme="dark"] .viz-root {
  color-scheme: dark;
  --page: #0d0d0d; --surface-1: #1a1a19;
  --text-primary: #f0efec; --text-secondary: #c3c2b7; --muted: #898781;
  --grid: #2c2c2a; --axis: #383835; --border: rgba(255,255,255,0.10);
  --series-1: #3987e5; --series-2: #d95926; --series-3: #199e70; --series-4: #c98500; --series-5: #d55181;
  --link: #52514e;
}
html, body { margin: 0; }
.viz-root { background: var(--page); color: var(--text-primary); min-height: 100vh;
  font: 14px/1.45 system-ui, -apple-system, "Segoe UI", sans-serif; padding: 20px 24px 40px; box-sizing: border-box; }
h1 { font-size: 20px; margin: 0 0 2px; font-weight: 600; }
h2 { font-size: 15px; margin: 0 0 10px; font-weight: 600; }
.sub { color: var(--text-secondary); font-size: 12px; }
.note { color: var(--muted); font-size: 12px; margin-top: 8px; }
.bar { display: flex; gap: 12px; align-items: center; flex-wrap: wrap; margin: 16px 0; }
.bar label { color: var(--text-secondary); font-size: 13px; }
button, select { font: inherit; font-size: 13px; color: var(--text-primary); background: var(--surface-1);
  border: 1px solid var(--border); border-radius: 6px; padding: 4px 10px; cursor: pointer; }
.seg { display: inline-flex; }
.seg button { border-radius: 0; margin-left: -1px; }
.seg button:first-child { border-radius: 6px 0 0 6px; margin-left: 0; }
.seg button:last-child { border-radius: 0 6px 6px 0; }
button[aria-pressed=true], button[aria-selected=true] { border-color: var(--text-secondary); font-weight: 600; }
input[type=range] { width: 300px; }
.tiles { display: flex; gap: 12px; flex-wrap: wrap; margin-bottom: 16px; }
.tile { background: var(--surface-1); border: 1px solid var(--border); border-radius: 10px; padding: 10px 16px; min-width: 140px; }
.tile .v { font-size: 22px; font-weight: 600; }
.tile .k { color: var(--text-secondary); font-size: 12px; }
.card { background: var(--surface-1); border: 1px solid var(--border); border-radius: 10px; padding: 16px; margin-bottom: 16px; overflow-x: auto; }
.legend { display: flex; gap: 16px; flex-wrap: wrap; align-items: center; font-size: 12px; color: var(--text-secondary); margin-bottom: 8px; }
.legend span { display: inline-flex; align-items: center; gap: 6px; }
.legend i { display: inline-block; width: 18px; height: 2px; border-radius: 1px; }
.legend i.thick { height: 6px; border-radius: 3px; }
.legend i.sq { width: 12px; height: 12px; border-radius: 2px; background: var(--text-primary); }
.legend i.dia { width: 10px; height: 10px; border: 1.5px solid var(--text-primary); transform: rotate(45deg); background: none; }
svg text { fill: var(--text-secondary); font-size: 11px; }
svg .frame { fill: none; stroke: var(--grid); }
svg .frame-title { fill: var(--text-primary); font-size: 13px; font-weight: 600; }
svg .vx rect.box { fill: var(--text-primary); }
svg .vx text.id { fill: var(--surface-1); font-size: 14px; font-weight: 600; }
svg .vx.hollow rect.box, svg .vx.hollow path.box { fill: var(--surface-1); stroke: var(--text-primary); stroke-width: 1.5; }
svg .vx.hollow text.id { fill: var(--text-primary); font-size: 11px; }
svg .vx.hostmem rect.box { fill: var(--page); stroke: var(--axis); }
svg .vx.hostmem text.id { fill: var(--text-secondary); font-size: 11px; font-weight: 600; }
svg .vx.pinned rect.box, svg .vx.pinned path.box { stroke: var(--series-2); stroke-width: 3; }
svg .rank { fill: var(--text-secondary); font-size: 10.5px; }
svg .lk path.vis { fill: none; stroke-linecap: round; }
svg .lk text.lbl { fill: var(--text-primary); font-size: 11px; font-weight: 600; paint-order: stroke; stroke: var(--surface-1); stroke-width: 4px; stroke-linejoin: round; }
svg .dim { opacity: 0.1; }
svg .vx.dim { opacity: 0.3; }
svg .callout rect { fill: var(--surface-1); stroke: var(--text-primary); stroke-width: 1; }
svg .callout text { fill: var(--text-primary); font: 11.5px ui-monospace, SFMono-Regular, Menlo, Consolas, monospace; }
svg .callout text.h { font-weight: 700; }
svg .callout text.x { fill: var(--muted); font-family: system-ui, sans-serif; }
svg .leader { fill: none; stroke: var(--text-primary); stroke-width: 1; }
#tip { position: fixed; pointer-events: none; background: var(--surface-1); color: var(--text-primary);
  border: 1px solid var(--border); border-radius: 8px; padding: 8px 10px; font-size: 12px;
  box-shadow: 0 4px 16px rgba(0,0,0,0.12); display: none; max-width: 380px; z-index: 10; }
#tip .val { font-weight: 600; font-size: 13px; }
#tip .row { display: flex; gap: 8px; align-items: center; }
#tip i { display: inline-block; width: 12px; height: 2px; flex: none; }
table { border-collapse: collapse; width: 100%; font-size: 12px; }
th, td { text-align: left; padding: 5px 8px; border-bottom: 1px solid var(--grid); white-space: nowrap; }
th { color: var(--text-secondary); font-weight: 600; }
td.num { text-align: right; font-variant-numeric: tabular-nums; }
.tabs { display: flex; gap: 6px; margin-bottom: 10px; flex-wrap: wrap; }
.empty { color: var(--muted); font-size: 13px; padding: 8px 0; }
</style>
</head>
<body>
<div class="viz-root" id="root">
  <h1>Level Zero fabric topology</h1>
  <div class="sub" id="meta"></div>
  <div class="bar">
    <span class="seg" role="group" aria-label="View" id="views"></span>
    <button id="play" type="button">Play</button>
    <label for="scrub">Time</label>
    <input id="scrub" type="range" min="0" max="0" value="0">
    <span class="sub" id="when"></span>
    <label for="mode">Show</label>
    <select id="mode"><option value="cum">Everything up to selected time</option><option value="win">Only the selected interval</option></select>
    <button id="clear" type="button">Clear pinned details</button>
    <button id="theme" type="button">Toggle theme</button>
  </div>
  <div class="tiles" id="tiles"></div>
  <div class="card">
    <h2 id="graph-title">Topology</h2>
    <div class="legend" id="legend"></div>
    <div id="graph"></div>
    <div class="note">Hover a device, switch or link to highlight its connections. Click to pin its details; click the detail box to unpin.</div>
  </div>
  <div class="card">
    <h2>Between hosts</h2>
    <div id="hosts"></div>
    <div class="note">Cross-host rows appear when copies touch memory owned by another host's devices (for example Xe Link scale-out). Traffic carried by network adapters (RDMA, Ethernet) is not visible to Level Zero.</div>
  </div>
  <div class="card">
    <h2>Throughput over time</h2>
    <div class="legend" id="legend2"></div>
    <div id="timeline"></div>
  </div>
  <div class="card">
    <div class="tabs" role="tablist" id="tabs"></div>
    <div id="table"></div>
  </div>
  <div id="tip"></div>
</div>
<script id="data" type="application/json">__DATA__</script>
<script>
(function () {
  "use strict";
  const D = JSON.parse(document.getElementById("data").textContent);
  const SVGNS = "http://www.w3.org/2000/svg";
  const CAT = D.categories.map((c, i) => Object.assign({}, c, { color: "var(--series-" + (i + 1) + ")" }));
  const catById = Object.fromEntries(CAT.map(c => [c.id, c]));
  const nodes = Object.fromEntries(D.nodes.map(n => [n.id, n]));
  const procs = Object.fromEntries(D.processes.map(p => [p.key, p]));
  const BIN_S = D.bins.width_us / 1e6;
  const store = (() => { try { return window.localStorage; } catch (e) { return null; } })();
  const saved = k => store && store.getItem("ftv." + k);
  const save = (k, v) => { if (store) store.setItem("ftv." + k, v); };
  const state = {
    bin: D.bins.n - 1,
    mode: saved("mode") || "cum",
    tab: saved("tab") || "links",
    view: saved("view") || (D.fabric.length ? "topology" : "throughput"),
    pins: JSON.parse(saved("pins") || "[]"),
    hover: null,
  };
  if (saved("theme")) document.documentElement.dataset.theme = saved("theme");
  // #view=throughput&pins=["n:..."]&mode=win&bin=12&theme=dark overrides saved state (shareable links).
  try {
    const h = new URLSearchParams(location.hash.slice(1));
    if (h.get("view")) state.view = h.get("view");
    if (h.get("pins")) state.pins = JSON.parse(h.get("pins"));
    if (h.get("mode")) state.mode = h.get("mode");
    if (h.get("bin")) state.bin = Math.max(0, Math.min(D.bins.n - 1, Number(h.get("bin"))));
    if (h.get("theme")) document.documentElement.dataset.theme = h.get("theme");
  } catch (e) { /* ignore malformed hash */ }

  // Link models get categorical slots in a fixed order: MDFI and XeLink first.
  const MODEL_SLOTS = ["var(--series-1)", "var(--series-3)", "var(--series-2)", "var(--series-4)", "var(--series-5)"];
  const models = [...new Set(D.fabric.map(e => e.model || "unknown"))].sort((a, b) => {
    const rank = m => (m === "MDFI" ? 0 : m === "XeLink" ? 1 : 2);
    return rank(a) - rank(b) || a.localeCompare(b);
  });
  const modelColor = m => MODEL_SLOTS[models.indexOf(m || "unknown")] || "var(--muted)";

  // ---- small helpers ---------------------------------------------------------
  function el(tag, attrs, parent) {
    const e = document.createElement(tag);
    for (const k in (attrs || {})) e.setAttribute(k, attrs[k]);
    if (parent) parent.appendChild(e);
    return e;
  }
  function svg(tag, attrs, parent) {
    const e = document.createElementNS(SVGNS, tag);
    for (const k in (attrs || {})) e.setAttribute(k, attrs[k]);
    if (parent) parent.appendChild(e);
    return e;
  }
  function text(parent, s) { parent.appendChild(document.createTextNode(s)); return parent; }
  function fmtBytes(n) {
    const u = ["B", "KiB", "MiB", "GiB", "TiB"]; let i = 0;
    while (Math.abs(n) >= 1024 && i < u.length - 1) { n /= 1024; i++; }
    return (i ? n.toFixed(1) : String(Math.round(n))) + " " + u[i];
  }
  function fmtRate(bps) {
    const u = ["B/s", "KB/s", "MB/s", "GB/s", "TB/s"]; let i = 0;
    while (Math.abs(bps) >= 1000 && i < u.length - 1) { bps /= 1000; i++; }
    return (i ? bps.toFixed(1) : String(Math.round(bps))) + " " + u[i];
  }
  function fmtTime(us) { return new Date(us / 1000).toLocaleTimeString(); }
  function short(id) { const n = nodes[id]; return n ? (n.short || n.label || id) : "?"; }
  function nodeLabel(id) {
    const n = nodes[id]; if (!n) return id || "?";
    if (n.kind === "device") return n.host + " · " + n.short + " (" + n.label + ")";
    if (n.kind === "host") return n.host + " · host memory";
    return n.label;
  }
  function procLabel(k) { const p = procs[k]; if (!p) return k || "?"; return k + (p.rank != null ? " (rank " + p.rank + ")" : ""); }
  function hostOf(id) { const n = nodes[id]; return n ? (n.kind === "switch" || n.kind === "remote" ? "fabric" : n.host) : "?"; }
  function rootOf(id) { const n = nodes[id]; return n && n.sub && n.root ? n.root : id; }
  function designBps(e) { return e && e.bw_unit === "B/ns" ? e.bandwidth * 1e9 : null; }

  // ---- tooltip ---------------------------------------------------------------
  const tip = document.getElementById("tip");
  function showTip(evt, lines) {
    tip.replaceChildren();
    lines.forEach((l, i) => {
      const row = el("div", { class: "row" }, tip);
      if (l.color) { const k = el("i", {}, row); k.style.background = l.color; }
      text(el("span", { class: i === 0 ? "val" : "" }, row), l.text);
    });
    tip.style.display = "block";
    tip.style.left = Math.min(evt.clientX + 14, window.innerWidth - tip.offsetWidth - 8) + "px";
    tip.style.top = Math.min(evt.clientY + 14, window.innerHeight - tip.offsetHeight - 8) + "px";
  }
  function hideTip() { tip.style.display = "none"; }

  // ---- selection & aggregation ------------------------------------------------
  function selectedFlows() {
    const lo = state.mode === "win" ? state.bin : 0;
    return D.flows.filter(f => f[0] >= lo && f[0] <= state.bin);
  }
  function selectionSeconds() { return ((state.mode === "win" ? 1 : state.bin + 1) * BIN_S) || 1; }
  function aggregate(flows) {
    const m = new Map();
    for (const [bin, a, b, cat, pkey, peer, bytes, ops] of flows) {
      const k = a + "|" + b + "|" + cat;
      let v = m.get(k);
      if (!v) { v = { key: "t:" + k, a, b, cat, bytes: 0, ops: 0, procs: new Map(), bins: new Map() }; m.set(k, v); }
      v.bytes += bytes; v.ops += ops;
      v.procs.set(pkey, (v.procs.get(pkey) || 0) + bytes);
      v.bins.set(bin, (v.bins.get(bin) || 0) + bytes);
    }
    const secs = selectionSeconds();
    for (const v of m.values()) { v.avg = v.bytes / secs; v.peak = Math.max(0, ...v.bins.values()) / BIN_S; }
    return [...m.values()].sort((x, y) => y.bytes - x.bytes);
  }
  // Achieved throughput between two endpoints (tiles of a card count for the card).
  function between(links, a, b) {
    const match = (x, y) => x === y || rootOf(x) === y;
    const out = { ab: { bytes: 0, peak: 0, avg: 0 }, ba: { bytes: 0, peak: 0, avg: 0 } };
    for (const l of links) {
      if (l.cat === "local") continue;
      const dir = match(l.a, a) && match(l.b, b) ? out.ab : match(l.a, b) && match(l.b, a) ? out.ba : null;
      if (!dir) continue;
      dir.bytes += l.bytes; dir.avg += l.avg; dir.peak = Math.max(dir.peak, l.peak);
    }
    return out;
  }
  function sharedLinks() {
    const m = new Map();
    for (const s of D.ipc) {
      if (!s.source || !s.importer_device) continue;
      const k = s.source + "|" + s.importer_device;
      let v = m.get(k);
      if (!v) { v = { key: "s:" + k, a: s.source, b: s.importer_device, bytes: 0, count: 0, pairs: new Set() }; m.set(k, v); }
      v.bytes += s.size || 0; v.count += 1; v.pairs.add(procLabel(s.exporter) + " → " + procLabel(s.importer));
    }
    return [...m.values()].sort((x, y) => y.bytes - x.bytes);
  }

  // ---- layout -----------------------------------------------------------------
  const S = 44, FRAME_PAD = 34, CALLOUT_W = 400;
  let L = null;
  function computeLayout() {
    const pos = {};
    const cols = Math.min(3, Math.max(1, D.hosts.length));
    const specs = D.hosts.map(h => {
      const devs = D.nodes.filter(n => n.host === h && n.kind === "device");
      const roots = devs.filter(n => !(n.sub && n.root && nodes[n.root])).sort((a, b) => (a.card || 0) - (b.card || 0));
      const groups = roots.map(r => {
        const subs = devs.filter(n => n.sub && n.root === r.id).sort((a, b) => (a.sub_id || 0) - (b.sub_id || 0));
        return { root: r.id, ids: subs.length ? subs.map(n => n.id) : [r.id], hasSubs: subs.length > 0 };
      });
      const leaves = groups.reduce((s, g) => s + g.ids.length, 0);
      const R = Math.max(110, ((leaves + groups.length * 0.7) * (S + 20)) / (2 * Math.PI));
      const side = 2 * R + 2 * S + 2 * FRAME_PAD + 70;
      return { h, groups, R, w: side, hgt: side + 24, leaves };
    });
    let y = 0;
    for (let r = 0; r * cols < specs.length; r++) {
      const row = specs.slice(r * cols, r * cols + cols);
      let x = 0;
      row.forEach(sp => { sp.x = x; sp.y = y; x += sp.w + 40; });
      y += Math.max(...row.map(s => s.hgt)) + 30;
    }
    const contentW = Math.max(320, ...specs.map(s => s.x + s.w));
    specs.forEach(sp => {
      sp.cx = sp.x + sp.w / 2; sp.cy = sp.y + 24 + (sp.hgt - 24) / 2;
      pos[sp.h + "|host"] = { x: sp.cx, y: sp.cy, host: sp.h };
      const step = 2 * Math.PI / Math.max(1, sp.groups.length);
      const delta = (S + 12) / sp.R;
      sp.groups.forEach((g, gi) => {
        const th = -Math.PI / 2 + gi * step;
        g.ids.forEach((id, i) => {
          const t = th + (i - (g.ids.length - 1) / 2) * delta;
          pos[id] = { x: sp.cx + sp.R * Math.cos(t), y: sp.cy + sp.R * Math.sin(t), theta: t, host: sp.h, ring: sp };
        });
        if (g.hasSubs) {
          const ps = g.ids.map(id => pos[id]);
          pos[g.root] = { x: ps.reduce((s, p) => s + p.x, 0) / ps.length, y: ps.reduce((s, p) => s + p.y, 0) / ps.length,
            theta: th, host: sp.h, ring: sp, virtual: true };
        }
      });
    });
    const band = D.nodes.filter(n => n.host === "fabric");
    let bandY = null;
    if (band.length) {
      bandY = y + 30;
      band.forEach((n, i) => { pos[n.id] = { x: (i + 1) * contentW / (band.length + 1), y: bandY, band: true }; });
      y = bandY + 70;
    }
    return { pos, specs, contentW, bandY, height: Math.max(y, 200), calloutX: contentW + 60 };
  }
  // Direction a link leaves a node: outward from a ring, upward from the fabric band.
  function exitDir(p) { return p.band ? { x: 0, y: -1 } : p.theta != null ? { x: Math.cos(p.theta), y: Math.sin(p.theta) } : { x: 0, y: 0 }; }
  // Distance from a node's centre to its edge, so arrowheads stay visible.
  function nodeRadius(p) { return p.band ? 30 : p.theta == null ? 40 : S / 2 + 6; }
  function linkPath(aId, bId, offset, trim) {
    let a = L.pos[aId], b = L.pos[bId];
    if (!a || !b) return null;
    const towards = (p, q, d) => { const l = Math.hypot(q.x - p.x, q.y - p.y) || 1; return Object.assign({}, p, { x: p.x + (q.x - p.x) / l * d, y: p.y + (q.y - p.y) / l * d }); };
    const off = offset || 0;
    const dx = b.x - a.x, dy = b.y - a.y, len = Math.hypot(dx, dy) || 1;
    const nx = -dy / len * off, ny = dx / len * off;
    const sameRing = a.ring && a.ring === b.ring;
    const isCenter = p => p.theta == null && !p.band;
    if (sameRing || isCenter(a) || isCenter(b)) {
      const c = { x: (a.x + b.x) / 2 + nx * 3, y: (a.y + b.y) / 2 + ny * 3 };
      if (trim) { const a0 = a; a = towards(a, off ? c : b, nodeRadius(a)); b = towards(b, off ? c : a0, nodeRadius(b)); }
      if (!off) return "M" + a.x + "," + a.y + " L" + b.x + "," + b.y;
      return "M" + a.x + "," + a.y + " Q" + c.x + "," + c.y + " " + b.x + "," + b.y;
    }
    // Leave a ring radially (short), approach the fabric band vertically (long),
    // so cross-host and switch links run around the rings instead of through them.
    const da = exitDir(a), db = exitDir(b);
    if (trim) { a = Object.assign({}, a, { x: a.x + da.x * nodeRadius(a), y: a.y + da.y * nodeRadius(a) });
                b = Object.assign({}, b, { x: b.x + db.x * nodeRadius(b), y: b.y + db.y * nodeRadius(b) }); }
    const ka = a.band ? Math.max(80, len * 0.4) : 60, kb = b.band ? Math.max(80, len * 0.4) : 60;
    const ax = a.x + da.x * ka + nx, ay = a.y + da.y * ka + ny, bx = b.x + db.x * kb + nx, by = b.y + db.y * kb + ny;
    return "M" + a.x + "," + a.y + " L" + (a.x + da.x * 22) + "," + (a.y + da.y * 22) +
      " C" + ax + "," + ay + " " + bx + "," + by + " " + (b.x + db.x * 22) + "," + (b.y + db.y * 22) + " L" + b.x + "," + b.y;
  }

  // ---- graph ---------------------------------------------------------------------
  let reg = { links: [], nodes: [] };
  function renderGraph(links) {
    const host = document.getElementById("graph");
    host.replaceChildren();
    reg = { links: [], nodes: [] };
    if (!D.nodes.length) { text(el("div", { class: "empty" }, host), "No topology records found."); return; }
    L = L || computeLayout();
    const W = L.calloutX + CALLOUT_W + 10;
    const s = svg("svg", { width: W, height: L.height, role: "img", "aria-label": "Fabric topology" }, host);
    const defs = svg("defs", {}, s);
    const marker = (id, color) => {
      const m = svg("marker", { id, viewBox: "0 0 10 10", refX: 9, refY: 5, markerWidth: 11, markerHeight: 11, markerUnits: "userSpaceOnUse", orient: "auto-start-reverse" }, defs);
      svg("path", { d: "M0,1 L9,5 L0,9 z" }, m).style.fill = color;
    };
    CAT.forEach(c => marker("arr-" + c.id, c.color));
    marker("arr-shared", "var(--series-1)");
    marker("arr-leader", "var(--text-primary)");

    // host frames
    for (const sp of L.specs) {
      svg("rect", { x: sp.x, y: sp.y, width: sp.w, height: sp.hgt, rx: 14, class: "frame" }, s);
      const nprocs = D.processes.filter(p => p.host === sp.h).length;
      const cards = sp.groups.length;
      const t = svg("text", { x: sp.x + 16, y: sp.y + 22, class: "frame-title" }, s);
      text(t, "Host " + sp.h);
      text(svg("text", { x: sp.x + 16, y: sp.y + 38 }, s), cards + " card(s), " + sp.leaves + " vertex(es), " + nprocs + " process(es)");
    }
    if (L.bandY != null) {
      svg("rect", { x: 0, y: L.bandY - 34, width: L.contentW, height: 68, rx: 14, class: "frame" }, s);
      text(svg("text", { x: 16, y: L.bandY - 16, class: "frame-title" }, s), "Fabric switches and remote vertices");
    }

    const linkLayer = svg("g", {}, s);
    const nodeLayer = svg("g", {}, s);
    const calloutLayer = svg("g", {}, s);

    function addLink(item, d, stroke, width, opts) {
      const g = svg("g", { class: "lk" }, linkLayer);
      const vis = svg("path", { d, class: "vis", "stroke-width": width }, g);
      vis.style.stroke = stroke;
      if (opts && opts.marker) vis.setAttribute("marker-end", "url(#" + opts.marker + ")");
      if (opts && opts.opacity) vis.style.opacity = opts.opacity;
      const hit = svg("path", { d, fill: "none", stroke: "transparent", "stroke-width": Math.max(14, width + 10) }, g);
      hit.style.cursor = "pointer";
      if (opts && opts.label) {
        const mid = vis.getTotalLength ? vis.getPointAtLength(vis.getTotalLength() / 2) : null;
        if (mid) text(svg("text", { x: mid.x, y: mid.y - 6, "text-anchor": "middle", class: "lbl" }, g), opts.label);
      }
      const entry = { el: g, path: vis, a: item.a, b: item.b, key: item.key, item };
      reg.links.push(entry);
      hit.addEventListener("pointermove", ev => { state.hover = item.key; applyFocus(); showTip(ev, tipFor(item.key)); });
      hit.addEventListener("pointerleave", () => { state.hover = null; applyFocus(); hideTip(); });
      hit.addEventListener("click", () => togglePin(item.key));
      return entry;
    }

    // fabric links: the topology itself
    const fabricItems = D.fabric.map(e => Object.assign({ key: "f:" + e.id + ":" + e.a + ":" + e.b }, e));
    for (const e of fabricItems) {
      const d = linkPath(e.a, e.b, 0); if (!d) continue;
      if (state.view === "topology") addLink(e, d, modelColor(e.model), e.intra ? 7 : 2.5);
      else addLink(e, d, "var(--link)", e.intra ? 4 : 1, { opacity: 0.8 });
    }

    // overlays
    if (state.view === "throughput") {
      const moving = links.filter(l => l.cat !== "local");
      const maxAvg = Math.max(1e-9, ...moving.map(l => l.avg));
      const labelled = new Set(moving.filter(l => l.avg >= maxAvg * 0.25).slice(0, 6).map(l => l.key));
      for (const l of moving) {
        const d = linkPath(l.a, l.b, 14, true); if (!d) continue;
        addLink(l, d, catById[l.cat].color, 2 + 9 * Math.sqrt(l.avg / maxAvg),
          { marker: "arr-" + l.cat, label: labelled.has(l.key) ? fmtRate(l.avg) : null });
      }
    } else if (state.view === "shared") {
      const shared = sharedLinks();
      const maxB = Math.max(1, ...shared.map(l => l.bytes));
      shared.forEach((l, i) => {
        const d = linkPath(l.a, l.b, 14, true); if (!d) return;
        addLink(l, d, "var(--series-1)", 2 + 8 * Math.sqrt(l.bytes / maxB), { marker: "arr-shared", label: i < 6 ? fmtBytes(l.bytes) : null });
      });
    }

    // vertices
    const ranksOn = new Map();
    D.processes.forEach(p => p.devices.forEach(d => { if (!ranksOn.has(d)) ranksOn.set(d, []); ranksOn.get(d).push(p); }));
    for (const n of D.nodes) {
      const p = L.pos[n.id];
      if (!p || p.virtual) continue;
      if (n.kind === "host" && state.view !== "throughput") continue; // host memory only matters for traffic
      const cls = n.kind === "device" ? "" : n.kind === "host" ? " hostmem" : " hollow";
      const g = svg("g", { class: "vx" + cls + (state.pins.includes("n:" + n.id) ? " pinned" : ""), tabindex: 0 }, nodeLayer);
      if (n.kind === "switch") {
        svg("path", { class: "box", d: "M" + p.x + "," + (p.y - 26) + " L" + (p.x + 26) + "," + p.y + " L" + p.x + "," + (p.y + 26) + " L" + (p.x - 26) + "," + p.y + " Z" }, g);
      } else if (n.kind === "host") {
        svg("rect", { class: "box", x: p.x - 38, y: p.y - 16, width: 76, height: 32, rx: 8 }, g);
      } else {
        const rot = p.theta != null ? (p.theta * 180 / Math.PI + 90) : 0;
        svg("rect", { class: "box", x: -S / 2, y: -S / 2, width: S, height: S, rx: 3, transform: "translate(" + p.x + "," + p.y + ") rotate(" + rot + ")" }, g);
      }
      const lbl = n.kind === "host" ? "host mem" : (n.short || "?");
      text(svg("text", { x: p.x, y: p.y + 5, "text-anchor": "middle", class: "id" }, g), lbl);
      if (p.theta != null) {
        const users = (ranksOn.get(n.id) || []).map(pr => pr.rank != null ? "r" + pr.rank : "pid " + pr.pid);
        if (users.length) {
          const rr = p.ring.R + S * 0.95, c = Math.cos(p.theta);
          const t = svg("text", { x: p.ring.cx + rr * c, y: p.ring.cy + rr * Math.sin(p.theta) + 4, class: "rank",
            "text-anchor": Math.abs(c) < 0.3 ? "middle" : c > 0 ? "start" : "end" }, g);
          text(t, users.length > 3 ? users.slice(0, 3).join(" ") + " +" + (users.length - 3) : users.join(" "));
        }
      } else if (n.kind !== "host") {
        text(svg("text", { x: p.x, y: p.y + 44, "text-anchor": "middle" }, g), n.label || "");
      }
      reg.nodes.push({ el: g, id: n.id });
      const key = "n:" + n.id;
      g.addEventListener("pointermove", ev => { state.hover = key; applyFocus(); showTip(ev, tipFor(key)); });
      g.addEventListener("pointerleave", () => { state.hover = null; applyFocus(); hideTip(); });
      g.addEventListener("focus", () => { state.hover = key; applyFocus(); });
      g.addEventListener("blur", () => { state.hover = null; applyFocus(); });
      g.addEventListener("click", () => togglePin(key));
      g.addEventListener("keydown", ev => { if (ev.key === "Enter" || ev.key === " ") { ev.preventDefault(); togglePin(key); } });
    }

    const bottom = renderCallouts(calloutLayer, links);
    s.setAttribute("height", Math.max(L.height, bottom + 10)); // callouts may stack below the graph
    applyFocus();
  }

  function applyFocus() {
    const keys = state.hover ? [state.hover] : state.pins;
    if (!keys.length) { reg.links.forEach(l => l.el.classList.remove("dim")); reg.nodes.forEach(n => n.el.classList.remove("dim")); return; }
    const fn = new Set(), fl = new Set();
    const touches = (l, id) => l.a === id || l.b === id || l.a === rootOf(id) || l.b === rootOf(id);
    for (const k of keys) {
      if (k.startsWith("n:")) {
        const id = k.slice(2); fn.add(id);
        reg.links.forEach(l => { if (touches(l, id)) { fl.add(l.key); fn.add(l.a); fn.add(l.b); } });
      } else {
        const l = reg.links.find(x => x.key === k);
        if (l) { fl.add(k); fn.add(l.a); fn.add(l.b); }
      }
    }
    // Links attached to a card (root) light up both of its tiles.
    for (const id of [...fn]) D.nodes.forEach(n => { if (n.root === id && n.sub) fn.add(n.id); });
    reg.links.forEach(l => l.el.classList.toggle("dim", !fl.has(l.key)));
    reg.nodes.forEach(n => n.el.classList.toggle("dim", !fn.has(n.id)));
  }
  function togglePin(key) {
    const i = state.pins.indexOf(key);
    if (i >= 0) state.pins.splice(i, 1); else state.pins.push(key);
    save("pins", JSON.stringify(state.pins));
    hideTip();
    render();
  }

  // ---- details (tooltips and pinned callouts) ---------------------------------------
  const DUPLEX = { full: "ZE_FABRIC_EDGE_EXP_DUPLEXITY_FULL_DUPLEX", half: "ZE_FABRIC_EDGE_EXP_DUPLEXITY_HALF_DUPLEX" };
  function rateLine(label, dir, design) {
    if (!dir.bytes) return label + ": no traffic";
    let s = label + ": avg " + fmtRate(dir.avg) + ", peak " + fmtRate(dir.peak);
    if (design) s += " (" + (100 * dir.peak / design).toFixed(1) + "% of design)";
    return s;
  }
  function detailLines(key, links) {
    // Returns { head, body: [], extra: [] }: body in struct notation, extra in plain text.
    if (key.startsWith("n:")) {
      const n = nodes[key.slice(2)]; if (!n) return null;
      const out = links.filter(l => l.a === n.id && l.cat !== "local"), inn = links.filter(l => l.b === n.id && l.cat !== "local");
      const sum = (arr, f) => arr.reduce((s, l) => s + l[f], 0);
      const extra = [];
      if (n.kind === "host") {
        extra.push("host to devices: avg " + fmtRate(sum(out, "avg")) + ", devices to host: avg " + fmtRate(sum(inn, "avg")));
        extra.push(D.processes.filter(p => p.host === n.host).length + " process(es) on this host");
        return { head: "Host memory · " + n.host, body: [], extra };
      }
      if (n.name) extra.push(n.name + " · host " + n.host);
      const users = D.processes.filter(p => p.devices.includes(n.id)).map(p => procLabel(p.key));
      if (users.length) extra.push("used by " + users.join(", "));
      extra.push("out avg " + fmtRate(sum(out, "avg")) + " · in avg " + fmtRate(sum(inn, "avg")));
      const exp = D.ipc.filter(s => s.source === n.id).reduce((s, x) => s + (x.size || 0), 0);
      const imp = D.ipc.filter(s => s.importer_device === n.id).reduce((s, x) => s + (x.size || 0), 0);
      if (exp || imp) extra.push("memory shared: exported " + fmtBytes(exp) + ", imported " + fmtBytes(imp));
      const v = n.vertex;
      if (v) {
        return { head: "ze_fabric_vertex_handle_t " + (n.short || n.label), body: [
          "ze_fabric_vertex_exp_properties_t = {", "  uuid = '" + (v.uuid || v.id) + "',",
          "  type = ZE_FABRIC_VERTEX_EXP_TYPE_" + String(v.type || "unknown").toUpperCase() + ",",
          "  remote = " + (v.remote ? "true" : "false") + ",", "  address = " + (v.pci || "?"), "}"], extra };
      }
      return { head: "ze_device_handle_t " + (n.short || n.label), body: [
        "uuid    = " + (n.uuid || "?"), "address = " + (n.pci || "?"), n.sub ? "tile " + n.sub_id + " of card " + n.card : "card " + n.card], extra };
    }
    if (key.startsWith("f:")) {
      const e = D.fabric.find(x => "f:" + x.id + ":" + x.a + ":" + x.b === key); if (!e) return null;
      const t = between(links, e.a, e.b), design = designBps(e);
      return { head: "ze_fabric_edge_handle_t " + short(e.a) + " ↔ " + short(e.b), body: [
        "ze_fabric_edge_exp_properties_t = {", "  uuid = '" + e.id + "',", "  model = '" + e.model + "',",
        "  bandwidth = " + e.bandwidth + " " + e.bw_unit + ",", "  latency = " + e.latency + " " + e.lat_unit + ",",
        "  duplexity = " + (DUPLEX[e.duplexity] || "UNKNOWN"), "}"],
        extra: [nodeLabel(e.a) + " ↔ " + nodeLabel(e.b),
          rateLine("achieved " + short(e.a) + " → " + short(e.b), t.ab, design),
          rateLine("achieved " + short(e.b) + " → " + short(e.a), t.ba, design)] };
    }
    if (key.startsWith("t:")) {
      const l = links.find(x => x.key === key); if (!l) return null;
      const fab = D.fabric.find(e => (e.a === l.a || e.a === rootOf(l.a)) && (e.b === l.b || e.b === rootOf(l.b)) ||
        (e.b === l.a || e.b === rootOf(l.a)) && (e.a === l.b || e.a === rootOf(l.b)));
      const design = designBps(fab);
      const extra = [catById[l.cat].label + " · " + fmtBytes(l.bytes) + " in " + l.ops + " op(s)",
        "avg " + fmtRate(l.avg) + " · peak " + fmtRate(l.peak) + (design ? " (" + (100 * l.peak / design).toFixed(1) + "% of " + fab.model + " design)" : "")];
      extra.push(fab ? "direct fabric link: " + fab.model + " " + fab.bandwidth + " " + fab.bw_unit : "no direct fabric link reported");
      [...l.procs.entries()].sort((x, y) => y[1] - x[1]).slice(0, 4).forEach(([k, v]) => extra.push(procLabel(k) + ": " + fmtBytes(v)));
      return { head: "Throughput " + nodeLabel(l.a) + " → " + nodeLabel(l.b), body: [], extra };
    }
    if (key.startsWith("s:")) {
      const l = sharedLinks().find(x => x.key === key); if (!l) return null;
      return { head: "Shared memory " + short(l.a) + " → " + short(l.b), body: [],
        extra: [fmtBytes(l.bytes) + " in " + l.count + " IPC import(s)", nodeLabel(l.a) + " → " + nodeLabel(l.b), ...[...l.pairs].slice(0, 4)] };
    }
    return null;
  }
  let lastLinks = [];
  function tipFor(key) {
    const d = detailLines(key, lastLinks); if (!d) return [{ text: key }];
    return [{ text: d.head }, ...d.extra.map(t => ({ text: t }))];
  }
  function anchorOf(key) {
    if (key.startsWith("n:")) { const p = L.pos[key.slice(2)]; return p ? { x: p.x, y: p.y } : null; }
    const l = reg.links.find(x => x.key === key);
    if (!l) return null;
    const len = l.path.getTotalLength();
    return l.path.getPointAtLength(len / 2);
  }
  function renderCallouts(layer, links) {
    const placed = [];
    const items = state.pins.map(k => ({ k, a: anchorOf(k), d: detailLines(k, links) })).filter(x => x.a && x.d);
    items.sort((p, q) => p.a.y - q.a.y);
    let nextY = 10;
    for (const it of items) {
      const lines = [{ t: it.d.head, c: "h" }, ...it.d.body.map(t => ({ t, c: "" })), ...it.d.extra.map(t => ({ t, c: "x" }))];
      const h = 16 + lines.length * 16;
      const y = Math.max(nextY, it.a.y - h / 2);
      nextY = y + h + 12;
      const g = svg("g", { class: "callout" }, layer);
      g.style.cursor = "pointer";
      const x = L.calloutX;
      svg("rect", { x, y, width: CALLOUT_W, height: h, rx: 10 }, g);
      lines.forEach((ln, i) => {
        const t = svg("text", { x: x + 12, y: y + 20 + i * 16, class: ln.c }, g);
        text(t, ln.t.length > 58 ? ln.t.slice(0, 57) + "…" : ln.t);
      });
      const sx = x, sy = y + Math.min(h / 2, 24);
      svg("path", { class: "leader", d: "M" + sx + "," + sy + " C" + (sx - 60) + "," + sy + " " + (it.a.x + 60) + "," + it.a.y + " " + (it.a.x + 4) + "," + it.a.y,
        "marker-end": "url(#arr-leader)" }, layer);
      g.addEventListener("click", () => togglePin(it.k));
      placed.push(g);
    }
    return nextY;
  }

  // ---- header, tiles, legend ----------------------------------------------------------
  function renderMeta() {
    const m = document.getElementById("meta");
    m.replaceChildren();
    text(m, "Generated " + D.generated + " from " + D.sources.length + " stream(s) · " + D.hosts.length + " host(s) · bin " +
      (D.bins.width_us / 1000).toFixed(1) + " ms");
  }
  function renderTiles(links) {
    const t = document.getElementById("tiles");
    t.replaceChildren();
    const moving = links.filter(l => l.cat !== "local");
    const perBin = new Map();
    moving.forEach(l => l.bins.forEach((b, k) => perBin.set(k, (perBin.get(k) || 0) + b)));
    const peak = Math.max(0, ...perBin.values()) / BIN_S;
    const shared = D.ipc.filter(s => s.exporter).reduce((s, x) => s + (x.size || 0), 0);
    const devs = D.nodes.filter(n => n.kind === "device" && !D.nodes.some(c => c.root === n.id)).length;
    const sw = D.nodes.filter(n => n.kind === "switch").length;
    [[fmtBytes(moving.reduce((s, l) => s + l.bytes, 0)), "Moved across links"], [fmtRate(peak), "Peak aggregate throughput"],
     [fmtBytes(shared), "Memory shared over IPC"], [String(D.processes.length), "Processes"],
     [String(devs), "Devices / tiles"], [String(D.fabric.length), "Fabric links"], [String(sw), "Switches"]].forEach(([v, k]) => {
      const d = el("div", { class: "tile" }, t);
      text(el("div", { class: "v" }, d), v);
      text(el("div", { class: "k" }, d), k);
    });
  }
  function legendItem(lg, cls, color, label) {
    const s = el("span", {}, lg); const i = el("i", { class: cls || "" }, s);
    if (color) i.style.background = color;
    text(s, label);
  }
  function renderLegend() {
    const lg = document.getElementById("legend");
    lg.replaceChildren();
    legendItem(lg, "sq", null, "Device tile (card.tile)");
    if (D.nodes.some(n => n.kind === "switch")) legendItem(lg, "dia", null, "Fabric switch");
    if (state.view === "topology") {
      models.forEach(m => legendItem(lg, "", modelColor(m), m + " link"));
      if (D.fabric.some(e => e.intra)) legendItem(lg, "thick", "var(--muted)", "Thick = link inside one card");
      if (!D.fabric.length) text(el("span", {}, lg), "No fabric links reported by the driver (zeFabricEdgeGetExp)");
    } else if (state.view === "throughput") {
      CAT.filter(c => c.id !== "local").forEach(c => legendItem(lg, "", c.color, c.label));
      legendItem(lg, "", "var(--link)", "Fabric link");
      text(el("span", {}, lg), "Width = average throughput");
    } else {
      legendItem(lg, "", "var(--series-1)", "IPC shared memory, exporter → importer (width = bytes shared)");
    }
    document.getElementById("graph-title").textContent =
      state.view === "topology" ? "Topology" : state.view === "throughput" ? "Achieved throughput" : "Shared memory";
    const lg2 = document.getElementById("legend2");
    lg2.replaceChildren();
    CAT.forEach(c => legendItem(lg2, "", c.color, c.label));
  }

  // ---- between hosts ---------------------------------------------------------------------
  function renderHosts(links) {
    const host = document.getElementById("hosts");
    host.replaceChildren();
    const m = new Map();
    const row = (a, b) => { const k = a + "\u0000" + b; if (!m.has(k)) m.set(k, { a, b, bytes: 0, avg: 0, bins: new Map(), shared: 0, imports: 0 }); return m.get(k); };
    for (const l of links) {
      if (l.cat === "local") continue;
      const r = row(hostOf(l.a), hostOf(l.b));
      r.bytes += l.bytes; r.avg += l.avg;
      l.bins.forEach((b, k) => r.bins.set(k, (r.bins.get(k) || 0) + b));
    }
    for (const s of D.ipc) {
      if (!s.exporter_host) continue;
      const r = row(s.exporter_host, s.importer_host);
      r.shared += s.size || 0; r.imports += 1;
    }
    const rows = [...m.values()].sort((x, y) => y.bytes - x.bytes).map(r => [
      r.a === r.b ? r.a + " (within host)" : r.a, r.a === r.b ? "" : r.b, fmtBytes(r.bytes), fmtRate(r.avg),
      fmtRate(Math.max(0, ...r.bins.values()) / BIN_S), r.imports ? fmtBytes(r.shared) + " (" + r.imports + ")" : "-"]);
    table(host, ["From host", "To host", "Bytes moved", "Avg throughput", "Peak throughput", "Memory shared (imports)"], rows, [2, 3, 4, 5]);
  }

  // ---- timeline ------------------------------------------------------------------------
  function renderTimeline() {
    const host = document.getElementById("timeline");
    host.replaceChildren();
    const n = D.bins.n;
    const series = CAT.map(() => new Float64Array(n));
    const idx = Object.fromEntries(CAT.map((c, i) => [c.id, i]));
    for (const f of D.flows) series[idx[f[3]]][f[0]] += f[6] / BIN_S;
    const used = CAT.map((c, i) => series[i].some(v => v > 0));
    if (!used.some(Boolean)) { text(el("div", { class: "empty" }, host), "No data movement recorded yet."); return; }
    const W = Math.max(640, Math.min(1200, host.clientWidth || 900)), H = 220, PL = 76, PR = 16, PT = 10, PB = 28;
    const maxV = Math.max(1, ...series.flatMap((s, i) => used[i] ? Array.from(s) : [0]));
    const xs = i => PL + (n === 1 ? 0 : i * (W - PL - PR) / (n - 1));
    const ys = v => PT + (H - PT - PB) * (1 - v / maxV);
    const s = svg("svg", { width: W, height: H, role: "img", "aria-label": "Throughput over time by category" }, host);
    for (let k = 0; k <= 4; k++) {
      const v = maxV * k / 4, y = ys(v);
      svg("line", { x1: PL, x2: W - PR, y1: y, y2: y }, s).style.stroke = k ? "var(--grid)" : "var(--axis)";
      const t = svg("text", { x: PL - 8, y: y + 4, "text-anchor": "end" }, s); t.style.fontVariantNumeric = "tabular-nums"; text(t, fmtRate(v));
    }
    [0, Math.floor((n - 1) / 2), n - 1].forEach(i => text(svg("text", { x: xs(i), y: H - 8, "text-anchor": i === 0 ? "start" : i === n - 1 ? "end" : "middle" }, s),
      fmtTime(D.bins.t0_us + (i + 1) * D.bins.width_us)));
    const lo = state.mode === "win" ? state.bin : 0;
    const band = svg("rect", { x: xs(lo) - 3, y: PT, width: Math.max(6, xs(state.bin) - xs(lo) + 6), height: H - PT - PB }, s);
    band.style.fill = "var(--grid)"; band.style.opacity = "0.6";
    CAT.forEach((c, i) => {
      if (!used[i]) return;
      let d = ""; for (let j = 0; j < n; j++) d += (j ? "L" : "M") + xs(j) + "," + ys(series[i][j]);
      svg("path", { d, fill: "none", "stroke-width": 2, "stroke-linejoin": "round" }, s).style.stroke = c.color;
    });
    const cross = svg("line", { y1: PT, y2: H - PB, visibility: "hidden" }, s); cross.style.stroke = "var(--muted)";
    const hit = svg("rect", { x: PL, y: PT, width: W - PL - PR, height: H - PT - PB, fill: "transparent" }, s);
    const pick = ev => { const r = s.getBoundingClientRect(); return Math.max(0, Math.min(n - 1, Math.round((ev.clientX - r.left - PL) / ((W - PL - PR) / Math.max(1, n - 1))))); };
    hit.addEventListener("pointermove", ev => {
      const j = pick(ev); cross.setAttribute("x1", xs(j)); cross.setAttribute("x2", xs(j)); cross.setAttribute("visibility", "visible");
      const lines = [{ text: fmtTime(D.bins.t0_us + (j + 1) * D.bins.width_us) }];
      CAT.forEach((c, i) => { if (used[i]) lines.push({ text: fmtRate(series[i][j]) + "  " + c.label, color: c.color }); });
      showTip(ev, lines);
    });
    hit.addEventListener("pointerleave", () => { cross.setAttribute("visibility", "hidden"); hideTip(); });
    hit.addEventListener("click", ev => setBin(pick(ev)));
  }

  // ---- tables ----------------------------------------------------------------------------
  const TABS = [["links", "Links"], ["procs", "Processes"], ["pairs", "Process pairs"], ["ipc", "IPC sharing"], ["devices", "Devices"], ["fabric", "Fabric and P2P"]];
  function table(parent, head, rows, numeric) {
    if (!rows.length) { text(el("div", { class: "empty" }, parent), "Nothing recorded for this selection."); return; }
    const t = el("table", {}, parent);
    const tr = el("tr", {}, el("thead", {}, t));
    head.forEach(h => text(el("th", {}, tr), h));
    const tb = el("tbody", {}, t);
    rows.forEach(r => { const row = el("tr", {}, tb); r.forEach((c, i) => text(el("td", numeric && numeric.includes(i) ? { class: "num" } : {}, row), c == null ? "" : String(c))); });
  }
  function renderTabs(links, flows) {
    const tabs = document.getElementById("tabs");
    tabs.replaceChildren();
    TABS.forEach(([id, label]) => {
      const b = el("button", { type: "button", role: "tab", "aria-selected": String(state.tab === id) }, tabs);
      text(b, label);
      b.addEventListener("click", () => { state.tab = id; save("tab", id); render(); });
    });
    const host = document.getElementById("table");
    host.replaceChildren();
    if (state.tab === "links") {
      table(host, ["From", "To", "Kind", "Bytes", "Avg throughput", "Peak throughput", "Ops", "Processes"], links.map(l => [nodeLabel(l.a),
        l.a === l.b ? "(same device)" : nodeLabel(l.b), catById[l.cat].label, fmtBytes(l.bytes), fmtRate(l.avg), fmtRate(l.peak), l.ops,
        [...l.procs.keys()].map(procLabel).join(", ")]), [3, 4, 5, 6]);
    } else if (state.tab === "procs") {
      const bytes = new Map(); flows.forEach(f => bytes.set(f[4], (bytes.get(f[4]) || 0) + f[6]));
      table(host, ["Process", "Rank", "Executable", "Devices used", "Bytes moved", "Status"], D.processes.map(p => [p.key, p.rank, p.exe,
        p.devices.map(d => nodes[d] ? nodes[d].short : d).join(", "), fmtBytes(bytes.get(p.key) || 0), p.ended ? "exited" : "running or crashed"]), [4]);
    } else if (state.tab === "pairs") {
      const m = new Map();
      flows.filter(f => f[5]).forEach(f => { const k = [f[4], f[5]].sort().map(procLabel).join(" ↔ "); m.set(k, (m.get(k) || 0) + f[6]); });
      const secs = selectionSeconds();
      table(host, ["Processes", "Bytes exchanged", "Avg throughput"], [...m.entries()].sort((a, b) => b[1] - a[1]).map(([k, v]) => [k, fmtBytes(v), fmtRate(v / secs)]), [1, 2]);
    } else if (state.tab === "ipc") {
      table(host, ["Importer", "Opened on", "Exporter", "Memory of", "Size", "Kind", "Join"], D.ipc.map(l => [procLabel(l.importer),
        l.importer_device ? nodeLabel(l.importer_device) : "", l.exporter ? procLabel(l.exporter) : "not found", l.source ? nodeLabel(l.source) : "",
        fmtBytes(l.size || 0), l.kind, l.join]), [4]);
    } else if (state.tab === "devices") {
      table(host, ["Host", "Id", "PCI / tile", "Name", "UUID"], D.nodes.filter(n => n.kind === "device").map(n => [n.host, n.short, n.label,
        n.name || "", n.uuid || ""]));
    } else {
      const rows = D.fabric.map(e => ["fabric", nodeLabel(e.a), nodeLabel(e.b), e.model, e.bandwidth + " " + e.bw_unit, e.latency + " " + e.lat_unit, e.duplexity]);
      D.p2p.forEach(e => rows.push(["p2p", nodeLabel(e.a), nodeLabel(e.b), (e.access ? "access" : "no access") + (e.atomics ? " + atomics" : ""),
        e.logical_bw != null ? e.logical_bw + " " + e.bw_unit : "", e.logical_lat != null ? e.logical_lat + " " + e.lat_unit : "", ""]));
      table(host, ["Source", "A", "B", "Model / access", "Bandwidth", "Latency", "Duplex"], rows);
    }
  }

  // ---- controls ----------------------------------------------------------------------------
  const scrub = document.getElementById("scrub"), when = document.getElementById("when"), mode = document.getElementById("mode");
  scrub.max = String(Math.max(0, D.bins.n - 1));
  mode.value = state.mode;
  function setBin(i) { state.bin = i; render(); }
  scrub.addEventListener("input", () => setBin(Number(scrub.value)));
  mode.addEventListener("change", () => { state.mode = mode.value; save("mode", mode.value); render(); });
  document.getElementById("clear").addEventListener("click", () => { state.pins = []; save("pins", "[]"); render(); });
  document.getElementById("theme").addEventListener("click", () => {
    const dark = getComputedStyle(document.getElementById("root")).colorScheme === "dark";
    document.documentElement.dataset.theme = dark ? "light" : "dark";
    save("theme", document.documentElement.dataset.theme);
    render();
  });
  const views = document.getElementById("views");
  [["topology", "Topology"], ["throughput", "Throughput"], ["shared", "Shared memory"]].forEach(([id, label]) => {
    const b = el("button", { type: "button", "data-view": id }, views);
    text(b, label);
    b.addEventListener("click", () => { state.view = id; save("view", id); render(); });
  });
  let timer = null;
  const playBtn = document.getElementById("play");
  playBtn.addEventListener("click", () => {
    if (timer) { clearInterval(timer); timer = null; playBtn.textContent = "Play"; return; }
    if (state.bin >= D.bins.n - 1) state.bin = 0;
    playBtn.textContent = "Pause";
    timer = setInterval(() => { if (state.bin >= D.bins.n - 1) { playBtn.click(); return; } setBin(state.bin + 1); }, 150);
  });

  function render() {
    scrub.value = String(state.bin);
    when.replaceChildren(); text(when, fmtTime(D.bins.t0_us + (state.bin + 1) * D.bins.width_us));
    views.querySelectorAll("button").forEach(b => b.setAttribute("aria-pressed", String(b.dataset.view === state.view)));
    const flows = selectedFlows();
    const links = aggregate(flows);
    lastLinks = links;
    renderMeta(); renderTiles(links); renderLegend();
    renderGraph(links); renderHosts(links); renderTimeline(); renderTabs(links, flows);
  }
  render();
})();
</script>
</body>
</html>
"""


def write_html(data, path, refresh_s=None):
    payload = json.dumps(data, separators=(",", ":")).replace("</", "<\\/")
    refresh = '<meta http-equiv="refresh" content="%d">' % refresh_s if refresh_s else ""
    html = HTML_TEMPLATE.replace("__REFRESH__", refresh).replace("__DATA__", payload)
    tmp = path + ".tmp"
    with open(tmp, "w", encoding="utf-8") as fh:
        fh.write(html)
    os.replace(tmp, path)  # atomic, so a reloading browser never sees a partial page


def build(paths):
    files = collect_files(paths)
    model = Model(read_records(files))
    return model, model.to_json([os.path.basename(f) for f in files]), files


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("paths", nargs="+", help="output directories and/or .jsonl files (globs allowed)")
    ap.add_argument("--html", metavar="FILE", help="write a self-contained HTML report")
    ap.add_argument("--json", metavar="FILE", help="write the merged model as JSON")
    ap.add_argument("--watch", metavar="SECONDS", type=float,
                    help="keep regenerating the report every SECONDS (the HTML page reloads itself)")
    ap.add_argument("--quiet", action="store_true", help="do not print the text summary")
    ap.add_argument("--top", type=int, default=25, metavar="N",
                    help="number of links listed in the text summary (0 = all, default 25)")
    args = ap.parse_args(argv)

    while True:
        model, data, files = build(args.paths)
        if not files:
            print("no .jsonl files found in: %s" % ", ".join(args.paths), file=sys.stderr)
            if not args.watch:
                return 1
        if args.json:
            with open(args.json, "w", encoding="utf-8") as fh:
                json.dump(data, fh, indent=1)
        if args.html:
            write_html(data, args.html, int(max(1, round(args.watch))) if args.watch else None)
        if not args.quiet and not args.watch:
            print_summary(model, data, args.top)
        if not args.watch:
            if args.html:
                print("\nHTML report: %s" % os.path.abspath(args.html))
            return 0
        print("[%s] %d stream(s), %d flow rows -> %s" % (time.strftime("%H:%M:%S"), len(files), len(data["flows"]),
                                                         args.html or "(no --html)"), file=sys.stderr)
        try:
            time.sleep(args.watch)
        except KeyboardInterrupt:
            return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except BrokenPipeError:  # e.g. piped into head
        sys.stderr.close()
        sys.exit(0)
