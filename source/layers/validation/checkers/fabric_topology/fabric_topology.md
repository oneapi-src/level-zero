# Fabric Topology Checker

## Overview

The Fabric Topology checker records, for every process, what the GPU fabric looks like and how the workload moves data across it. It is intended for debugging scale-up (multi-GPU, multi-tile) and scale-out (multi-node) setups, where you need to answer:

- Which devices, tiles and fabric links does each process see? How are they connected (MDFI, Xe Link, switches)?
- Which processes run on which devices, and which processes share memory with each other?
- How many bytes moved between host memory, devices and other processes' memory, and at what throughput over time?

Each process writes a JSON Lines stream. `scripts/fabric_topology_viewer.py` merges the streams from any number of processes and hosts. It joins IPC exports to their imports, so traffic is attributed across processes, and produces a text summary and an interactive HTML report.

**Platform support:** Linux and Windows. On Windows, IPC exports and imports are joined by handle only, because the dma-buf join described below is Linux-only.

## Usage

```bash
export ZE_ENABLE_VALIDATION_LAYER=1
export ZEL_ENABLE_FABRIC_TOPOLOGY_CHECKER=1
export ZEL_FABRIC_TOPOLOGY_OUTPUT=/shared/ftc      # directory; one file per process
export ZEL_FABRIC_TOPOLOGY_INTERVAL_MS=1000        # optional, traffic aggregation interval (default 1000)

mpirun -n 12 ./my_workload                          # or vLLM, torchrun, ...

python3 scripts/fabric_topology_viewer.py /shared/ftc --html fabric.html
```

| Variable | Meaning |
|---|---|
| `ZEL_ENABLE_FABRIC_TOPOLOGY_CHECKER` | Enables the checker. |
| `ZEL_FABRIC_TOPOLOGY_OUTPUT` | Output directory (created if missing). Each process writes `fabric_topology_<host>_<pid>.jsonl`. Without it the checker only logs a summary to the loader log at exit. |
| `ZEL_FABRIC_TOPOLOGY_INTERVAL_MS` | Traffic is aggregated in memory and written once per interval. `0` writes every submission immediately (useful for tests; expensive for real workloads). |

### Multi-node

Point `ZEL_FABRIC_TOPOLOGY_OUTPUT` at a shared filesystem, or copy each node's directory to one place, and pass all directories to the viewer. Devices are identified by host and UUID, and fabric vertices by their fabric UUID, so a link that one node reports as *remote* is drawn to the matching tile on the other node.

### Watching a running workload

```bash
python3 scripts/fabric_topology_viewer.py /shared/ftc --html fabric.html --watch 2
```

This command regenerates the report every 2 seconds, and the page reloads itself. The view, time mode and pinned details are kept across reloads. Data appears once per `ZEL_FABRIC_TOPOLOGY_INTERVAL_MS`.

## The HTML report

The report is a single self-contained file and needs no network access. It contains:

- **Topology view:** one frame per host. Each host's devices sit on a ring labelled `card.tile`: cards are ordered by PCI address, and the tile is the sub-device index. Fabric links are coloured by model, and links inside a card (MDFI) are drawn thick. Fabric switches and unresolved remote vertices appear in a separate band below the hosts. Ranks are shown next to the tiles they use.
- **Throughput view:** achieved traffic per path, drawn as arrows whose width shows average throughput, with host memory at the centre of each ring.
- **Shared memory view:** IPC exporter-to-importer links, sized by the bytes shared.
- **Hover and pin:** hovering highlights an element's connections. Clicking pins a detail box with the `ze_fabric_vertex_exp_properties_t` / `ze_fabric_edge_exp_properties_t` contents plus achieved throughput for the current time selection. For a fabric link this is shown as a percentage of the link's design bandwidth.
- **Time scrubber:** shows either everything up to a point in time or a single interval. **Play** animates the run.
- **Between hosts:** bytes, average and peak throughput, and shared memory for each pair of hosts.
- **Throughput over time:** throughput by category, plus tables for links, processes, process pairs, IPC sharing, devices, and fabric/P2P properties.

The URL hash can preselect state for sharing a view, for example `fabric.html#view=throughput&mode=win&bin=20`.

## What is recorded

| Source | Recorded as |
|---|---|
| `zeInitDrivers` (or legacy `zeInit` + `zeDriverGet`) | As soon as the loader completes the call, the checker enumerates each driver's devices itself, even if the application only asked for the driver count. It writes one `topology` record per driver: devices and sub-devices (`zeDeviceGetProperties`, PCI address), the P2P matrix (`zeDeviceGetP2PProperties` with the bandwidth extension when supported), fabric vertices and edges (`zeFabricVertexGetExp`, `zeFabricEdgeGetExp` and their properties), and `fabric_query` diagnostics. `zeDeviceGet` is a fallback trigger, and it retries a driver whose fabric tables were not yet available. |
| `zeMemAllocDevice/Host/Shared`, `zeMemFree[Ext]` | Address ranges mapped to the device (or host) that owns them. |
| `zeCommandListAppendMemoryCopy`, `CopyRegion`, `CopyFromContext`, `Fill` | Bytes attributed to (executing device, source location, destination location). |
| Immediate command lists | Counted at append time. |
| Regular command lists | Recorded at append time and counted on **every** `zeCommandQueueExecuteCommandLists` / `zeCommandListImmediateAppendCommandListsExp`, so replays are counted correctly. |
| `zeMemGetIpcHandle[WithProperties]` | An `ipc_export` record carrying join keys. |
| `zeMemOpenIpcHandle`, external dma-buf fd imports in `zeMemAllocDevice/Shared` | An `ipc_import` record with the same join keys. Copies touching the imported range are attributed to the exporting process and device. |

### How IPC is joined across processes

Both sides record:

- `handle_hash`: a hash of the 64-byte IPC handle. It matches whenever the handle bytes are passed between processes unchanged.
- `dmabuf_ino` (Linux): the inode of the dma-buf behind the handle. It matches even when a framework re-creates the handle around a re-numbered descriptor (SCM_RIGHTS, `pidfd_getfd`).

The viewer prefers `handle_hash` and falls back to `dmabuf_ino`. Unmatched imports are reported as `unresolved`, for example an external fd from a NIC or from a process that was not traced.

### How a transfer maps to links

A copy executed by device E reads from its source and writes to its destination. Data crosses `src -> E` when the source is not E's memory, and `E -> dst` when the destination is not E's memory. Each crossing is categorised as host-to-device, device-to-host, device-to-device, cross-process (IPC), or on-device when nothing leaves E.

## Record format

Each line is one JSON object with `type`, `ts_us` (wall clock, microseconds), `host` and `pid`:

| `type` | Extra fields |
|---|---|
| `process_start` | `version`, `exe`, `interval_ms`, `env` (rank and device-selection variables such as `RANK`, `PMI_RANK`, `ZE_AFFINITY_MASK`) |
| `device` | `id` (`dev:<uuid>`), `uuid`, `name`, `dev_type`, `vendor_id`, `device_id`, `sub`, `sub_id`, `root`, `pci` |
| `topology` | `driver`, `devices[]`, `p2p[]` (`a`, `b`, `access`, `atomics`, bandwidth/latency), `fabric_vertices[]` (`id`, `uuid`, `type`, `remote`, `pci`, `device`, `parent`), `fabric_edges[]` (`id`, `a`, `b`, `model`, `bandwidth`, `bw_unit`, `latency`, `lat_unit`, `duplexity`), `fabric_query` (`vertex_table`, `edge_table`, `vertex_result`, `vertices`, `subvertices`, `duplicate_vertex_uuids`, `edge_pairs`, `edges`, `edge_errors`) |
| `traffic` | `t0_us`, `t1_us`, `edges[]` (`exec`, `src`, `dst`, `op`, `bytes`, `ops`), `mem` (live bytes per location) |
| `ipc_export` | `handle_hash`, `dmabuf_ino`, `loc`, `ptr`, `base`, `size` |
| `ipc_import` | `import_id`, `kind` (`ipc` or `external_fd`), `loc` (`ipc:<n>`), `device`, `ptr`, `base`, `size`, `handle_hash`, `dmabuf_ino` |
| `ipc_close` | `import_id` |
| `process_end` | `totals[]`: whole-run totals in the same form as `traffic.edges` |

A vertex `id` equals its `uuid` unless the driver reports the same UUID for several vertices. In that case `id` is made unique (`<uuid>@<host>#<index>`) so that distinct vertices are not merged. Edges refer to vertex `id`s. When the viewer finds no fabric links, it prints the `fabric_query` diagnostics with the reason.

Locations are `dev:<uuid>` (memory of a device or tile), `host` (host USM or pageable memory), or `ipc:<n>` (memory imported into this process; resolved by the viewer).

## Limitations

- **API-level accounting:** only copies and fills issued through Level Zero are counted. Kernels that load or store peer or IPC memory, which is how many collective libraries move data, do not appear in the throughput views. Hardware port counters (`zesFabricPortGetThroughput`) are needed for that and are planned as a follow-up.
- **Submission time, not execution time:** bytes are counted when submitted. Throughput is therefore *submitted* throughput per interval, which matches execution closely for synchronous immediate lists but can lead it for deep queues.
- **Network adapters:** scale-out traffic over network adapters (RDMA, Ethernet via oneCCL, MPI or libfabric) is invisible to Level Zero. What *is* visible: device buffers exported as dma-buf (unresolved `external_fd` imports), host staging copies, and fabric links that other nodes report as remote vertices.
- **Experimental fabric APIs:** `zeFabric*Exp` is experimental, and drivers that do not implement it produce rings without links. The P2P matrix is still recorded.
- **Other memory paths:** memory mapped through `zeVirtualMem*` or allocated by another context is classified via `zeMemGetAllocProperties`. Pageable host memory is reported as `host`.
