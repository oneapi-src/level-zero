/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_fabric_topology_checker.cpp
 *
 * Fabric Topology checker: records device / fabric topology and the data
 * movement issued by the workload as a JSON Lines stream per process. See
 * fabric_topology.md in this directory for the record format.
 *
 */
#include "zel_fabric_topology_checker.h"

#include <algorithm>
#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iterator>
#include <map>
#include <mutex>
#include <set>
#include <sstream>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#else
#include <climits>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

namespace validation_layer
{
    class fabricTopologyChecker fabric_topology_checker;

    namespace
    {
        ///////////////////////////////////////////////////////////////////////
        // Small helpers

        std::string jsonEscape(const std::string &s) {
            std::string out;
            out.reserve(s.size() + 2);
            for (unsigned char c : s) {
                switch (c) {
                case '"': out += "\\\""; break;
                case '\\': out += "\\\\"; break;
                case '\n': out += "\\n"; break;
                case '\r': out += "\\r"; break;
                case '\t': out += "\\t"; break;
                default:
                    if (c < 0x20) {
                        char buf[8];
                        snprintf(buf, sizeof(buf), "\\u%04x", c);
                        out += buf;
                    } else {
                        out += static_cast<char>(c);
                    }
                }
            }
            return out;
        }

        std::string quoted(const std::string &s) { return "\"" + jsonEscape(s) + "\""; }

        std::string hexBytes(const uint8_t *p, size_t n) {
            static const char digits[] = "0123456789abcdef";
            std::string out;
            out.reserve(n * 2);
            for (size_t i = 0; i < n; ++i) {
                out += digits[p[i] >> 4];
                out += digits[p[i] & 0xf];
            }
            return out;
        }

        std::string hexPtr(const void *p) {
            char buf[32];
            snprintf(buf, sizeof(buf), "0x%" PRIxPTR, reinterpret_cast<uintptr_t>(p));
            return buf;
        }

        std::string hex64(uint64_t v) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%016" PRIx64, v);
            return buf;
        }

        uint64_t fnv1a(const uint8_t *p, size_t n) {
            uint64_t h = 1469598103934665603ULL;
            for (size_t i = 0; i < n; ++i) {
                h ^= p[i];
                h *= 1099511628211ULL;
            }
            return h;
        }

        // Wall-clock time so streams from different processes / nodes can be aligned.
        uint64_t nowUs() {
            return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(
                                             std::chrono::system_clock::now().time_since_epoch())
                                             .count());
        }

        uint64_t currentPid() {
#ifdef _WIN32
            return static_cast<uint64_t>(GetCurrentProcessId());
#else
            return static_cast<uint64_t>(getpid());
#endif
        }

        std::string hostName() {
#ifdef _WIN32
            char buf[MAX_COMPUTERNAME_LENGTH + 1] = {};
            DWORD len = sizeof(buf);
            if (GetComputerNameA(buf, &len))
                return std::string(buf, len);
            return "unknown";
#else
            char buf[256] = {};
            if (gethostname(buf, sizeof(buf) - 1) == 0 && buf[0] != '\0')
                return buf;
            return "unknown";
#endif
        }

        std::string exePath() {
#ifdef _WIN32
            char buf[MAX_PATH] = {};
            DWORD len = GetModuleFileNameA(nullptr, buf, MAX_PATH);
            return std::string(buf, len);
#else
            char buf[4096] = {};
            ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
            return len > 0 ? std::string(buf, static_cast<size_t>(len)) : std::string();
#endif
        }

        void makeDirectory(const std::string &path) {
#ifdef _WIN32
            _mkdir(path.c_str());
#else
            mkdir(path.c_str(), 0775);
#endif
        }

        // Returns the inode of a dma-buf if `fd` is a dma-buf descriptor valid in
        // this process, 0 otherwise. The inode identifies the same dma-buf in every
        // process on the host, so it joins exporter and importer even when the
        // descriptor was re-numbered in transit (SCM_RIGHTS, pidfd_getfd).
        uint64_t dmabufInode(uint64_t fd) {
#ifdef _WIN32
            (void)fd;
            return 0;
#else
            if (fd > static_cast<uint64_t>(INT_MAX))
                return 0;
            char linkPath[64];
            snprintf(linkPath, sizeof(linkPath), "/proc/self/fd/%d", static_cast<int>(fd));
            char target[256] = {};
            ssize_t n = readlink(linkPath, target, sizeof(target) - 1);
            if (n <= 0)
                return 0;
            target[n] = '\0';
            if (strncmp(target, "/dmabuf:", 8) != 0 && strcmp(target, "anon_inode:dmabuf") != 0)
                return 0;
            struct stat st;
            if (fstat(static_cast<int>(fd), &st) != 0)
                return 0;
            return static_cast<uint64_t>(st.st_ino);
#endif
        }

        const char *bandwidthUnit(ze_bandwidth_unit_t u) {
            switch (u) {
            case ZE_BANDWIDTH_UNIT_BYTES_PER_NANOSEC: return "B/ns";
            case ZE_BANDWIDTH_UNIT_BYTES_PER_CLOCK: return "B/clk";
            default: return "unknown";
            }
        }

        const char *latencyUnit(ze_latency_unit_t u) {
            switch (u) {
            case ZE_LATENCY_UNIT_NANOSEC: return "ns";
            case ZE_LATENCY_UNIT_CLOCK: return "clk";
            case ZE_LATENCY_UNIT_HOP: return "hop";
            default: return "unknown";
            }
        }

        const char *vertexType(ze_fabric_vertex_exp_type_t t) {
            switch (t) {
            case ZE_FABRIC_VERTEX_EXP_TYPE_DEVICE: return "device";
            case ZE_FABRIC_VERTEX_EXP_TYPE_SUBDEVICE: return "subdevice";
            case ZE_FABRIC_VERTEX_EXP_TYPE_SWITCH: return "switch";
            default: return "unknown";
            }
        }

        const char *duplexity(ze_fabric_edge_exp_duplexity_t d) {
            switch (d) {
            case ZE_FABRIC_EDGE_EXP_DUPLEXITY_HALF_DUPLEX: return "half";
            case ZE_FABRIC_EDGE_EXP_DUPLEXITY_FULL_DUPLEX: return "full";
            default: return "unknown";
            }
        }

        const char *deviceType(ze_device_type_t t) {
            switch (t) {
            case ZE_DEVICE_TYPE_GPU: return "gpu";
            case ZE_DEVICE_TYPE_CPU: return "cpu";
            case ZE_DEVICE_TYPE_FPGA: return "fpga";
            case ZE_DEVICE_TYPE_MCA: return "mca";
            case ZE_DEVICE_TYPE_VPU: return "npu";
            default: return "unknown";
            }
        }

        // Environment variables that help label a process (rank, device selection).
        const char *const kLabelEnvVars[] = {
            "PMI_RANK", "PMI_SIZE", "PMIX_RANK", "OMPI_COMM_WORLD_RANK", "OMPI_COMM_WORLD_LOCAL_RANK",
            "MPI_LOCALRANKID", "SLURM_PROCID", "SLURM_LOCALID", "RANK", "LOCAL_RANK", "WORLD_SIZE",
            "ZE_AFFINITY_MASK", "ZE_FLAT_DEVICE_HIERARCHY", "ONEAPI_DEVICE_SELECTOR"};

        ///////////////////////////////////////////////////////////////////////
        // State

        // A memory "location" is a string id:
        //   "dev:<uuid>"  device (or device-affine shared) memory of a device
        //   "host"        host USM or pageable system memory
        //   "ipc:<n>"     memory imported from another process / external fd;
        //                 resolved to the exporter by the viewer via ipc_import
        //                 and ipc_export records.
        struct AllocInfo {
            size_t size = 0;
            std::string loc;
        };

        struct EdgeKey {
            std::string exec; // device whose engine executes the command
            std::string src;  // source location ("" for fill)
            std::string dst;  // destination location
            std::string op;   // copy | copy_region | copy_from_context | fill
            bool operator<(const EdgeKey &o) const {
                if (exec != o.exec) return exec < o.exec;
                if (src != o.src) return src < o.src;
                if (dst != o.dst) return dst < o.dst;
                return op < o.op;
            }
        };

        struct EdgeVal {
            uint64_t bytes = 0;
            uint64_t ops = 0;
        };

        using EdgeMap = std::map<EdgeKey, EdgeVal>;

        struct CmdListInfo {
            ze_device_handle_t device = nullptr;
            ze_context_handle_t context = nullptr;
            bool immediate = false;
            EdgeMap recorded; // regular lists: accounted on every execution
        };

        struct FabricState {
            std::mutex mtx;

            bool outputEnabled = false;
            std::ofstream out;
            std::string outPath;

            std::string host;
            uint64_t pid = 0;
            uint64_t intervalUs = 1000000;
            uint64_t intervalStartUs = 0;

            std::unordered_map<ze_device_handle_t, std::string> deviceLoc;
            std::set<std::string> emittedDeviceIds; // several handles may map to one device
            std::set<ze_driver_handle_t> snapshotDrivers;
            std::map<ze_driver_handle_t, int> snapshotAttempts;

            std::map<uintptr_t, AllocInfo> allocs;
            std::unordered_map<std::string, uint64_t> liveBytes;
            std::unordered_map<ze_command_list_handle_t, CmdListInfo> cmdLists;

            EdgeMap intervalEdges;
            EdgeMap totalEdges;

            std::set<uint64_t> exportedHashes;
            std::unordered_map<uintptr_t, uint64_t> importIdByPtr;
            uint64_t nextImportId = 0;
        };

        FabricState &state() {
            static FabricState instance;
            return instance;
        }

        ///////////////////////////////////////////////////////////////////////
        // Record emission (caller holds the lock)

        std::string recordHeader(FabricState &s, const char *type) {
            std::ostringstream os;
            os << "{\"type\":\"" << type << "\",\"ts_us\":" << nowUs() << ",\"host\":" << quoted(s.host)
               << ",\"pid\":" << s.pid;
            return os.str();
        }

        void emitLocked(FabricState &s, const std::string &record, bool flush) {
            if (!s.outputEnabled)
                return;
            s.out << record << '\n';
            if (flush)
                s.out.flush();
        }

        std::string edgesJson(const EdgeMap &edges) {
            std::ostringstream os;
            os << "[";
            bool first = true;
            for (const auto &e : edges) {
                if (!first) os << ",";
                first = false;
                os << "{\"exec\":" << quoted(e.first.exec)
                   << ",\"src\":" << (e.first.src.empty() ? std::string("null") : quoted(e.first.src))
                   << ",\"dst\":" << quoted(e.first.dst) << ",\"op\":" << quoted(e.first.op)
                   << ",\"bytes\":" << e.second.bytes << ",\"ops\":" << e.second.ops << "}";
            }
            os << "]";
            return os.str();
        }

        void flushIntervalLocked(FabricState &s, uint64_t now, bool force) {
            if (!force && now - s.intervalStartUs < s.intervalUs)
                return;
            if (!s.intervalEdges.empty()) {
                std::ostringstream os;
                os << recordHeader(s, "traffic") << ",\"t0_us\":" << s.intervalStartUs << ",\"t1_us\":" << now
                   << ",\"edges\":" << edgesJson(s.intervalEdges) << ",\"mem\":{";
                bool first = true;
                for (const auto &m : s.liveBytes) {
                    if (!first) os << ",";
                    first = false;
                    os << quoted(m.first) << ":" << m.second;
                }
                os << "}}";
                emitLocked(s, os.str(), true);
                s.intervalEdges.clear();
            }
            s.intervalStartUs = now;
        }

        void accountLocked(FabricState &s, const EdgeKey &key, uint64_t bytes, uint64_t ops) {
            auto &iv = s.intervalEdges[key];
            iv.bytes += bytes;
            iv.ops += ops;
            auto &tv = s.totalEdges[key];
            tv.bytes += bytes;
            tv.ops += ops;
        }

        ///////////////////////////////////////////////////////////////////////
        // Device resolution (caller holds the lock)

        std::string resolveDeviceLocked(FabricState &s, ze_device_handle_t hDevice) {
            if (hDevice == nullptr)
                return "host";
            auto it = s.deviceLoc.find(hDevice);
            if (it != s.deviceLoc.end())
                return it->second;

            auto &ddi = context.zeDdiTable;
            ze_device_properties_t props = {};
            props.stype = ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES;
            std::string uuid;
            bool haveProps = ddi.Device.pfnGetProperties &&
                             ddi.Device.pfnGetProperties(hDevice, &props) == ZE_RESULT_SUCCESS;
            if (haveProps) {
                uuid = hexBytes(props.uuid.id, ZE_MAX_DEVICE_UUID_SIZE);
            } else {
                uuid = "handle-" + hexPtr(hDevice);
            }
            std::string loc = "dev:" + uuid;
            // Insert before resolving the root device to keep recursion bounded.
            s.deviceLoc[hDevice] = loc;
            if (!s.emittedDeviceIds.insert(loc).second)
                return loc;

            bool isSub = haveProps && (props.flags & ZE_DEVICE_PROPERTY_FLAG_SUBDEVICE);
            std::string rootLoc;
            if (isSub && ddi.Device.pfnGetRootDevice) {
                ze_device_handle_t hRoot = nullptr;
                if (ddi.Device.pfnGetRootDevice(hDevice, &hRoot) == ZE_RESULT_SUCCESS && hRoot && hRoot != hDevice)
                    rootLoc = resolveDeviceLocked(s, hRoot);
            }

            std::string pci;
            if (ddi.Device.pfnPciGetPropertiesExt) {
                ze_pci_ext_properties_t pciProps = {};
                pciProps.stype = ZE_STRUCTURE_TYPE_PCI_EXT_PROPERTIES;
                if (ddi.Device.pfnPciGetPropertiesExt(hDevice, &pciProps) == ZE_RESULT_SUCCESS) {
                    char buf[64];
                    snprintf(buf, sizeof(buf), "%04x:%02x:%02x.%x", pciProps.address.domain, pciProps.address.bus,
                             pciProps.address.device, pciProps.address.function);
                    pci = buf;
                }
            }

            std::ostringstream os;
            os << recordHeader(s, "device") << ",\"id\":" << quoted(loc) << ",\"handle\":" << quoted(hexPtr(hDevice));
            if (haveProps) {
                std::string name(props.name, strnlen(props.name, ZE_MAX_DEVICE_NAME));
                os << ",\"uuid\":" << quoted(uuid) << ",\"name\":" << quoted(name) << ",\"dev_type\":\""
                   << deviceType(props.type) << "\",\"vendor_id\":" << props.vendorId
                   << ",\"device_id\":" << props.deviceId << ",\"sub\":" << (isSub ? "true" : "false");
                if (isSub)
                    os << ",\"sub_id\":" << props.subdeviceId;
            }
            if (!rootLoc.empty())
                os << ",\"root\":" << quoted(rootLoc);
            if (!pci.empty())
                os << ",\"pci\":" << quoted(pci);
            os << "}";
            emitLocked(s, os.str(), true);
            return loc;
        }

        ///////////////////////////////////////////////////////////////////////
        // Topology snapshot (caller holds the lock)

        template <typename T, typename Fn>
        std::vector<T> enumerate(Fn fn, ze_result_t *pResult = nullptr) {
            uint32_t count = 0;
            std::vector<T> items;
            ze_result_t r = fn(&count, nullptr);
            if (r == ZE_RESULT_SUCCESS && count) {
                items.resize(count);
                r = fn(&count, items.data());
                items.resize(r == ZE_RESULT_SUCCESS ? count : 0);
            }
            if (pResult)
                *pResult = r;
            return items;
        }

        std::string resultHex(ze_result_t r) {
            char buf[16];
            snprintf(buf, sizeof(buf), "0x%x", static_cast<unsigned>(r));
            return buf;
        }

        // Writes the "p2p" array for every ordered device pair.
        void appendP2P(std::ostringstream &os, const std::vector<ze_device_handle_t> &devices,
                       const std::vector<std::string> &deviceLocs) {
            auto &ddi = context.zeDdiTable;
            os << ",\"p2p\":[";
            bool first = true;
            if (ddi.Device.pfnGetP2PProperties) {
                for (size_t a = 0; a < devices.size(); ++a) {
                    for (size_t b = 0; b < devices.size(); ++b) {
                        if (a == b || devices[a] == devices[b])
                            continue;
                        ze_device_p2p_bandwidth_exp_properties_t bw = {};
                        bw.stype = ZE_STRUCTURE_TYPE_DEVICE_P2P_BANDWIDTH_EXP_PROPERTIES;
                        ze_device_p2p_properties_t p2p = {};
                        p2p.stype = ZE_STRUCTURE_TYPE_DEVICE_P2P_PROPERTIES;
                        p2p.pNext = &bw;
                        bool haveBw = true;
                        ze_result_t r = ddi.Device.pfnGetP2PProperties(devices[a], devices[b], &p2p);
                        if (r != ZE_RESULT_SUCCESS) {
                            // Retry without the bandwidth extension for drivers that reject it.
                            haveBw = false;
                            p2p.pNext = nullptr;
                            r = ddi.Device.pfnGetP2PProperties(devices[a], devices[b], &p2p);
                        }
                        if (r != ZE_RESULT_SUCCESS)
                            continue;
                        os << (first ? "" : ",") << "{\"a\":" << quoted(deviceLocs[a]) << ",\"b\":" << quoted(deviceLocs[b])
                           << ",\"access\":" << ((p2p.flags & ZE_DEVICE_P2P_PROPERTY_FLAG_ACCESS) ? "true" : "false")
                           << ",\"atomics\":" << ((p2p.flags & ZE_DEVICE_P2P_PROPERTY_FLAG_ATOMICS) ? "true" : "false");
                        if (haveBw && (bw.logicalBandwidth || bw.physicalBandwidth)) {
                            os << ",\"logical_bw\":" << bw.logicalBandwidth << ",\"physical_bw\":" << bw.physicalBandwidth
                               << ",\"bw_unit\":\"" << bandwidthUnit(bw.bandwidthUnit) << "\""
                               << ",\"logical_lat\":" << bw.logicalLatency << ",\"physical_lat\":" << bw.physicalLatency
                               << ",\"lat_unit\":\"" << latencyUnit(bw.latencyUnit) << "\"";
                        }
                        os << "}";
                        first = false;
                    }
                }
            }
            os << "]";
        }

        struct VertexInfo {
            ze_fabric_vertex_handle_t handle = nullptr;
            ze_fabric_vertex_exp_properties_t props = {};
            int parent = -1;       // index of the parent vertex, -1 for top level
            std::string uuid;      // as reported by the driver
            std::string id;        // unique id used by edges (uuid unless the driver repeats uuids)
            std::string device;    // "dev:<uuid>" when the vertex is a device / sub-device
        };

        // Writes the "fabric_vertices", "fabric_edges" and "fabric_query" members.
        // Returns false when the fabric DDI tables are not populated yet.
        bool appendFabric(FabricState &s, std::ostringstream &os, ze_driver_handle_t hDriver) {
            auto &fv = context.zeDdiTable.FabricVertexExp;
            auto &fe = context.zeDdiTable.FabricEdgeExp;
            const bool vertexTable = fv.pfnGetExp && fv.pfnGetPropertiesExp;
            const bool edgeTable = fe.pfnGetExp && fe.pfnGetPropertiesExp;

            std::vector<VertexInfo> vertices;
            ze_result_t vertexResult = ZE_RESULT_ERROR_UNINITIALIZED;
            size_t subvertices = 0;
            if (vertexTable) {
                auto collect = [&](ze_fabric_vertex_handle_t hVertex, int parent) {
                    VertexInfo v;
                    v.handle = hVertex;
                    v.parent = parent;
                    v.props.stype = ZE_STRUCTURE_TYPE_FABRIC_VERTEX_EXP_PROPERTIES;
                    if (fv.pfnGetPropertiesExp(hVertex, &v.props) != ZE_RESULT_SUCCESS)
                        return -1;
                    v.uuid = hexBytes(v.props.uuid.id, ZE_MAX_UUID_SIZE);
                    ze_device_handle_t hDevice = nullptr;
                    if (fv.pfnGetDeviceExp && fv.pfnGetDeviceExp(hVertex, &hDevice) == ZE_RESULT_SUCCESS && hDevice)
                        v.device = resolveDeviceLocked(s, hDevice);
                    vertices.push_back(v);
                    return static_cast<int>(vertices.size() - 1);
                };
                auto top = enumerate<ze_fabric_vertex_handle_t>(
                    [&](uint32_t *c, ze_fabric_vertex_handle_t *v) { return fv.pfnGetExp(hDriver, c, v); }, &vertexResult);
                for (auto hVertex : top) {
                    int idx = collect(hVertex, -1);
                    if (idx < 0 || !fv.pfnGetSubVerticesExp)
                        continue;
                    auto subs = enumerate<ze_fabric_vertex_handle_t>(
                        [&](uint32_t *c, ze_fabric_vertex_handle_t *v) { return fv.pfnGetSubVerticesExp(hVertex, c, v); });
                    for (auto hSub : subs)
                        subvertices += collect(hSub, idx) >= 0 ? 1 : 0;
                }
            }

            // Vertex uuids are meant to be unique, but do not let a driver that
            // repeats them (e.g. all zeros) collapse distinct vertices into one.
            std::map<std::string, int> uuidCount;
            for (const auto &v : vertices)
                uuidCount[v.uuid]++;
            size_t duplicates = 0;
            for (size_t i = 0; i < vertices.size(); ++i) {
                auto &v = vertices[i];
                if (uuidCount[v.uuid] > 1) {
                    v.id = v.uuid + "@" + s.host + "#" + std::to_string(i);
                    ++duplicates;
                } else {
                    v.id = v.uuid;
                }
            }

            os << ",\"fabric_vertices\":[";
            for (size_t i = 0; i < vertices.size(); ++i) {
                const auto &v = vertices[i];
                char pci[64];
                snprintf(pci, sizeof(pci), "%04x:%02x:%02x.%x", v.props.address.domain, v.props.address.bus,
                         v.props.address.device, v.props.address.function);
                os << (i ? "," : "") << "{\"id\":" << quoted(v.id) << ",\"uuid\":" << quoted(v.uuid) << ",\"type\":\""
                   << vertexType(v.props.type) << "\",\"remote\":" << (v.props.remote ? "true" : "false")
                   << ",\"pci\":" << quoted(pci);
                if (v.parent >= 0)
                    os << ",\"parent\":" << quoted(vertices[v.parent].id);
                if (!v.device.empty())
                    os << ",\"device\":" << quoted(v.device);
                os << "}";
            }

            os << "],\"fabric_edges\":[";
            size_t pairs = 0, edgeErrors = 0, edgeCount = 0;
            if (edgeTable) {
                bool first = true;
                std::set<std::string> seen;
                for (size_t a = 0; a < vertices.size(); ++a) {
                    for (size_t b = a + 1; b < vertices.size(); ++b) {
                        ++pairs;
                        ze_result_t r = ZE_RESULT_SUCCESS;
                        auto edges = enumerate<ze_fabric_edge_handle_t>([&](uint32_t *c, ze_fabric_edge_handle_t *e) {
                            return fe.pfnGetExp(vertices[a].handle, vertices[b].handle, c, e);
                        }, &r);
                        if (r != ZE_RESULT_SUCCESS)
                            ++edgeErrors;
                        for (auto hEdge : edges) {
                            ze_fabric_edge_exp_properties_t ep = {};
                            ep.stype = ZE_STRUCTURE_TYPE_FABRIC_EDGE_EXP_PROPERTIES;
                            if (fe.pfnGetPropertiesExp(hEdge, &ep) != ZE_RESULT_SUCCESS) {
                                ++edgeErrors;
                                continue;
                            }
                            std::string id = hexBytes(ep.uuid.id, ZE_MAX_UUID_SIZE);
                            if (!seen.insert(id + "|" + vertices[a].id + "|" + vertices[b].id).second)
                                continue;
                            std::string model(ep.model, strnlen(ep.model, ZE_MAX_FABRIC_EDGE_MODEL_EXP_SIZE));
                            os << (first ? "" : ",") << "{\"id\":" << quoted(id) << ",\"a\":" << quoted(vertices[a].id)
                               << ",\"b\":" << quoted(vertices[b].id) << ",\"model\":" << quoted(model)
                               << ",\"bandwidth\":" << ep.bandwidth << ",\"bw_unit\":\"" << bandwidthUnit(ep.bandwidthUnit)
                               << "\",\"latency\":" << ep.latency << ",\"lat_unit\":\"" << latencyUnit(ep.latencyUnit)
                               << "\",\"duplexity\":\"" << duplexity(ep.duplexity) << "\"}";
                            first = false;
                            ++edgeCount;
                        }
                    }
                }
            }
            os << "],\"fabric_query\":{\"vertex_table\":" << (vertexTable ? "true" : "false")
               << ",\"edge_table\":" << (edgeTable ? "true" : "false") << ",\"vertex_result\":\""
               << (vertexTable ? resultHex(vertexResult) : std::string("n/a")) << "\",\"vertices\":" << vertices.size()
               << ",\"subvertices\":" << subvertices << ",\"duplicate_vertex_uuids\":" << duplicates
               << ",\"edge_pairs\":" << pairs << ",\"edges\":" << edgeCount << ",\"edge_errors\":" << edgeErrors << "}";
            return vertexTable && edgeTable;
        }

        // Records the topology visible through hDriver: devices, sub-devices, P2P
        // matrix and the zeFabric*Exp vertices and edges. Runs right after the
        // loader completed the application's zeInitDrivers / zeDriverGet.
        void snapshotTopologyLocked(FabricState &s, ze_driver_handle_t hDriver) {
            if (hDriver == nullptr || s.snapshotDrivers.count(hDriver))
                return;
            auto &ddi = context.zeDdiTable;
            if (!ddi.Device.pfnGet)
                return;

            // Devices and sub-devices
            std::vector<ze_device_handle_t> devices;
            auto roots = enumerate<ze_device_handle_t>([&](uint32_t *c, ze_device_handle_t *d) {
                return ddi.Device.pfnGet(hDriver, c, d);
            });
            if (roots.empty())
                return; // nothing usable yet; try again on the next enumeration
            for (auto hRoot : roots) {
                devices.push_back(hRoot);
                if (ddi.Device.pfnGetSubDevices) {
                    auto subs = enumerate<ze_device_handle_t>([&](uint32_t *c, ze_device_handle_t *d) {
                        return ddi.Device.pfnGetSubDevices(hRoot, c, d);
                    });
                    devices.insert(devices.end(), subs.begin(), subs.end());
                }
            }
            std::vector<std::string> deviceLocs;
            for (auto hDevice : devices)
                deviceLocs.push_back(resolveDeviceLocked(s, hDevice));

            std::ostringstream os;
            os << recordHeader(s, "topology") << ",\"driver\":" << quoted(hexPtr(hDriver)) << ",\"devices\":[";
            for (size_t i = 0; i < deviceLocs.size(); ++i)
                os << (i ? "," : "") << quoted(deviceLocs[i]);
            os << "]";
            appendP2P(os, devices, deviceLocs);
            bool fabricReady = appendFabric(s, os, hDriver);
            os << "}";
            emitLocked(s, os.str(), true);

            // A driver without fabric tables is retried a few times in case they were
            // not populated yet; the viewer merges repeated topology records.
            if (fabricReady || ++s.snapshotAttempts[hDriver] >= 3)
                s.snapshotDrivers.insert(hDriver);
        }

        void snapshotDrivers(const std::vector<ze_driver_handle_t> &drivers) {
            auto &s = state();
            std::lock_guard<std::mutex> lock(s.mtx);
            for (auto hDriver : drivers)
                snapshotTopologyLocked(s, hDriver);
        }

        ///////////////////////////////////////////////////////////////////////
        // Memory ownership (caller holds the lock)

        const std::pair<const uintptr_t, AllocInfo> *findAllocLocked(FabricState &s, const void *ptr) {
            uintptr_t p = reinterpret_cast<uintptr_t>(ptr);
            auto it = s.allocs.upper_bound(p);
            if (it == s.allocs.begin())
                return nullptr;
            --it;
            size_t extent = it->second.size ? it->second.size : 1;
            if (p - it->first < extent)
                return &*it;
            return nullptr;
        }

        void insertAllocLocked(FabricState &s, const void *base, size_t size, const std::string &loc) {
            uintptr_t b = reinterpret_cast<uintptr_t>(base);
            uintptr_t e = b + (size ? size : 1);
            // Drop stale entries that overlap the new range (e.g. address reuse
            // after a free we did not observe).
            auto it = s.allocs.upper_bound(b);
            if (it != s.allocs.begin()) {
                auto prev = std::prev(it);
                if (prev->first + (prev->second.size ? prev->second.size : 1) > b)
                    it = prev;
            }
            while (it != s.allocs.end() && it->first < e) {
                auto &lb = s.liveBytes[it->second.loc];
                lb -= std::min<uint64_t>(lb, it->second.size);
                it = s.allocs.erase(it);
            }
            AllocInfo info;
            info.size = size;
            info.loc = loc;
            s.allocs[b] = info;
            s.liveBytes[loc] += size;
        }

        void eraseAllocLocked(FabricState &s, const void *base) {
            auto it = s.allocs.find(reinterpret_cast<uintptr_t>(base));
            if (it == s.allocs.end())
                return;
            auto &lb = s.liveBytes[it->second.loc];
            lb -= std::min<uint64_t>(lb, it->second.size);
            s.allocs.erase(it);
        }

        std::string classifyLocked(FabricState &s, const void *ptr, ze_context_handle_t hContext) {
            if (ptr == nullptr)
                return "";
            if (auto alloc = findAllocLocked(s, ptr))
                return alloc->second.loc;
            // Not allocated through an API we intercept (pageable host memory,
            // virtual memory mappings, ...). Ask the driver.
            auto pfn = context.zeDdiTable.Mem.pfnGetAllocProperties;
            if (hContext && pfn) {
                ze_memory_allocation_properties_t props = {};
                props.stype = ZE_STRUCTURE_TYPE_MEMORY_ALLOCATION_PROPERTIES;
                ze_device_handle_t hDevice = nullptr;
                if (pfn(hContext, ptr, &props, &hDevice) == ZE_RESULT_SUCCESS &&
                    (props.type == ZE_MEMORY_TYPE_DEVICE || props.type == ZE_MEMORY_TYPE_SHARED) && hDevice)
                    return resolveDeviceLocked(s, hDevice);
            }
            return "host";
        }

        // Walks a descriptor pNext chain looking for an imported external fd.
        const ze_external_memory_import_fd_t *findImportFd(const void *pNext) {
            auto base = reinterpret_cast<const ze_base_desc_t *>(pNext);
            while (base) {
                if (base->stype == ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD)
                    return reinterpret_cast<const ze_external_memory_import_fd_t *>(base);
                base = reinterpret_cast<const ze_base_desc_t *>(base->pNext);
            }
            return nullptr;
        }

        uint64_t ipcHandleDmabufInode(ze_context_handle_t hContext, const ze_ipc_mem_handle_t &handle) {
            auto pfn = context.zeDdiTable.MemExp.pfnGetFileDescriptorFromIpcHandleExp;
            if (!pfn || !hContext)
                return 0;
            uint64_t fd = UINT64_MAX;
            if (pfn(hContext, handle, &fd) != ZE_RESULT_SUCCESS)
                return 0;
            return dmabufInode(fd);
        }

        // Registers memory that originates outside this process. Returns its "ipc:<n>" location.
        std::string registerImportLocked(FabricState &s, const char *kind, ze_context_handle_t hContext,
                                         ze_device_handle_t hDevice, const void *ptr, size_t size,
                                         const ze_ipc_mem_handle_t *handle, uint64_t inode) {
            uint64_t id = s.nextImportId++;
            std::string loc = "ipc:" + std::to_string(id);
            const void *base = ptr;
            if (size == 0) {
                auto pfn = context.zeDdiTable.Mem.pfnGetAddressRange;
                void *rangeBase = nullptr;
                size_t rangeSize = 0;
                if (pfn && hContext && pfn(hContext, ptr, &rangeBase, &rangeSize) == ZE_RESULT_SUCCESS && rangeBase &&
                    rangeSize) {
                    base = rangeBase;
                    size = rangeSize;
                }
            }
            insertAllocLocked(s, base, size, loc);
            s.importIdByPtr[reinterpret_cast<uintptr_t>(ptr)] = id;

            std::ostringstream os;
            os << recordHeader(s, "ipc_import") << ",\"import_id\":" << id << ",\"kind\":\"" << kind << "\""
               << ",\"loc\":" << quoted(loc) << ",\"device\":" << quoted(resolveDeviceLocked(s, hDevice))
               << ",\"ptr\":" << quoted(hexPtr(ptr)) << ",\"base\":" << quoted(hexPtr(base)) << ",\"size\":" << size;
            if (handle)
                os << ",\"handle_hash\":\"" << hex64(fnv1a(reinterpret_cast<const uint8_t *>(handle->data), ZE_MAX_IPC_HANDLE_SIZE)) << "\"";
            if (inode)
                os << ",\"dmabuf_ino\":" << inode;
            os << "}";
            emitLocked(s, os.str(), true);
            return loc;
        }

        void recordExportLocked(FabricState &s, ze_context_handle_t hContext, const void *ptr,
                                const ze_ipc_mem_handle_t &handle) {
            uint64_t hash = fnv1a(reinterpret_cast<const uint8_t *>(handle.data), ZE_MAX_IPC_HANDLE_SIZE);
            if (!s.exportedHashes.insert(hash).second)
                return; // frameworks commonly re-export the same buffer; report once
            const void *base = ptr;
            size_t size = 0;
            std::string loc;
            if (auto alloc = findAllocLocked(s, ptr)) {
                base = reinterpret_cast<const void *>(alloc->first);
                size = alloc->second.size;
                loc = alloc->second.loc;
            } else {
                loc = classifyLocked(s, ptr, hContext);
            }
            uint64_t inode = ipcHandleDmabufInode(hContext, handle);

            std::ostringstream os;
            os << recordHeader(s, "ipc_export") << ",\"handle_hash\":\"" << hex64(hash) << "\"";
            if (inode)
                os << ",\"dmabuf_ino\":" << inode;
            os << ",\"loc\":" << quoted(loc) << ",\"ptr\":" << quoted(hexPtr(ptr)) << ",\"base\":" << quoted(hexPtr(base))
               << ",\"size\":" << size << "}";
            emitLocked(s, os.str(), true);
        }

        ///////////////////////////////////////////////////////////////////////
        // Data movement

        void recordTransfer(ze_command_list_handle_t hCommandList, const void *dst, const void *src,
                            ze_context_handle_t hSrcContext, uint64_t bytes, const char *op) {
            auto &s = state();
            std::lock_guard<std::mutex> lock(s.mtx);

            EdgeKey key;
            key.op = op;
            auto it = s.cmdLists.find(hCommandList);
            ze_context_handle_t hContext = nullptr;
            bool immediate = true;
            if (it != s.cmdLists.end()) {
                key.exec = resolveDeviceLocked(s, it->second.device);
                hContext = it->second.context;
                immediate = it->second.immediate;
            } else {
                key.exec = "dev:unknown";
            }
            key.dst = classifyLocked(s, dst, hContext);
            if (src)
                key.src = classifyLocked(s, src, hSrcContext ? hSrcContext : hContext);

            if (!immediate) {
                auto &v = it->second.recorded[key];
                v.bytes += bytes;
                v.ops += 1;
                return;
            }
            accountLocked(s, key, bytes, 1);
            flushIntervalLocked(s, nowUs(), false);
        }

        void recordSubmission(uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists) {
            if (!phCommandLists)
                return;
            auto &s = state();
            std::lock_guard<std::mutex> lock(s.mtx);
            for (uint32_t i = 0; i < numCommandLists; ++i) {
                auto it = s.cmdLists.find(phCommandLists[i]);
                if (it == s.cmdLists.end())
                    continue;
                for (const auto &e : it->second.recorded)
                    accountLocked(s, e.first, e.second.bytes, e.second.ops);
            }
            flushIntervalLocked(s, nowUs(), false);
        }

        void trackCommandList(ze_command_list_handle_t hCommandList, ze_context_handle_t hContext,
                              ze_device_handle_t hDevice, bool immediate) {
            auto &s = state();
            std::lock_guard<std::mutex> lock(s.mtx);
            CmdListInfo info;
            info.device = hDevice;
            info.context = hContext;
            info.immediate = immediate;
            s.cmdLists[hCommandList] = info;
            resolveDeviceLocked(s, hDevice);
        }

    } // namespace

    ///////////////////////////////////////////////////////////////////////////
    // Construction / teardown

    fabricTopologyChecker::fabricTopologyChecker() {
        enableFabricTopology = getenv_tobool("ZEL_ENABLE_FABRIC_TOPOLOGY_CHECKER");
        if (!enableFabricTopology)
            return;

        auto &s = state();
        s.host = hostName();
        s.pid = currentPid();
        s.intervalStartUs = nowUs();

        std::string interval = getenv_string("ZEL_FABRIC_TOPOLOGY_INTERVAL_MS");
        if (!interval.empty()) {
            char *end = nullptr;
            unsigned long long ms = strtoull(interval.c_str(), &end, 10);
            if (end != interval.c_str())
                s.intervalUs = static_cast<uint64_t>(ms) * 1000;
        }

        std::string dir = getenv_string("ZEL_FABRIC_TOPOLOGY_OUTPUT");
        if (!dir.empty()) {
            makeDirectory(dir);
            std::string sep = (dir.back() == '/' || dir.back() == '\\') ? "" : "/";
            s.outPath = dir + sep + "fabric_topology_" + s.host + "_" + std::to_string(s.pid) + ".jsonl";
            s.out.open(s.outPath, std::ios::out | std::ios::trunc);
            s.outputEnabled = s.out.is_open() && s.out.good();
            if (!s.outputEnabled && context.logger)
                context.logger->log_error("Fabric Topology Checker: failed to open " + s.outPath);
        }

        if (s.outputEnabled) {
            std::ostringstream os;
            os << recordHeader(s, "process_start") << ",\"version\":1,\"exe\":" << quoted(exePath())
               << ",\"interval_ms\":" << (s.intervalUs / 1000) << ",\"env\":{";
            bool first = true;
            for (const char *name : kLabelEnvVars) {
                std::string value = getenv_string(name);
                if (value.empty())
                    continue;
                os << (first ? "" : ",") << quoted(name) << ":" << quoted(value);
                first = false;
            }
            os << "}}";
            emitLocked(s, os.str(), true);
        }
        if (context.logger)
            context.logger->log_info("Fabric Topology Checker enabled" +
                                     (s.outputEnabled ? ", writing " + s.outPath : std::string(", no output file")));

        zeValidation = new ZEfabricTopologyChecker;
        zesValidation = new ZESfabricTopologyChecker;
        zetValidation = new ZETfabricTopologyChecker;
        zerValidation = new ZERfabricTopologyChecker;
        validation_layer::context.validationHandlers.push_back(this);
    }

    fabricTopologyChecker::~fabricTopologyChecker() {
        if (!enableFabricTopology)
            return;
        {
            auto &s = state();
            std::lock_guard<std::mutex> lock(s.mtx);
            flushIntervalLocked(s, nowUs(), true);

            std::ostringstream summary;
            summary << "Fabric Topology Checker: data movement summary (exec | src -> dst | op | bytes | ops)";
            for (const auto &e : s.totalEdges) {
                summary << "\n  " << e.first.exec << " | " << (e.first.src.empty() ? "-" : e.first.src) << " -> "
                        << e.first.dst << " | " << e.first.op << " | " << e.second.bytes << " | " << e.second.ops;
            }
            if (context.logger)
                context.logger->log_info(summary.str());

            if (s.outputEnabled) {
                std::ostringstream os;
                os << recordHeader(s, "process_end") << ",\"totals\":" << edgesJson(s.totalEdges) << "}";
                emitLocked(s, os.str(), true);
                s.out.close();
                s.outputEnabled = false;
            }
        }
        delete zeValidation;
        delete zesValidation;
        delete zetValidation;
        delete zerValidation;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Topology discovery

    // The topology is populated as soon as the application's zeInitDrivers (or
    // legacy zeInit + zeDriverGet) has been completed by the loader. By then the
    // loader has initialized the drivers and ze_lib has populated this layer's DDI
    // tables, including the optional fabric tables, so the layer can enumerate
    // devices and query zeFabric*Exp itself. When the application only asked for
    // the driver count, the layer fetches the handles with the same descriptor.
    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeInitDriversEpilogue(
        uint32_t *pCount, ze_driver_handle_t *phDrivers, ze_init_driver_type_desc_t *desc, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !pCount || *pCount == 0)
            return ZE_RESULT_SUCCESS;
        std::vector<ze_driver_handle_t> drivers;
        if (phDrivers) {
            drivers.assign(phDrivers, phDrivers + *pCount);
        } else if (auto pfn = context.zeDdiTable.Global.pfnInitDrivers) {
            drivers = enumerate<ze_driver_handle_t>([&](uint32_t *c, ze_driver_handle_t *d) { return pfn(c, d, desc); });
        }
        snapshotDrivers(drivers);
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeDriverGetEpilogue(
        uint32_t *pCount, ze_driver_handle_t *phDrivers, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !pCount || *pCount == 0)
            return ZE_RESULT_SUCCESS;
        std::vector<ze_driver_handle_t> drivers;
        if (phDrivers) {
            drivers.assign(phDrivers, phDrivers + *pCount);
        } else if (auto pfn = context.zeDdiTable.Driver.pfnGet) {
            drivers = enumerate<ze_driver_handle_t>([&](uint32_t *c, ze_driver_handle_t *d) { return pfn(c, d); });
        }
        snapshotDrivers(drivers);
        return ZE_RESULT_SUCCESS;
    }

    // Fallback for drivers reached without the calls above (and for retries when
    // a driver's fabric tables were not available at the first snapshot).
    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeDeviceGetEpilogue(
        ze_driver_handle_t hDriver, uint32_t *, ze_device_handle_t *phDevices, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phDevices && hDriver)
            snapshotDrivers({hDriver});
        return ZE_RESULT_SUCCESS;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Memory ownership

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeMemAllocDeviceEpilogue(
        ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t *device_desc, size_t size, size_t,
        ze_device_handle_t hDevice, void **pptr, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !pptr || !*pptr)
            return ZE_RESULT_SUCCESS;
        auto &s = state();
        std::lock_guard<std::mutex> lock(s.mtx);
        auto importFd = device_desc ? findImportFd(device_desc->pNext) : nullptr;
        if (importFd) {
            registerImportLocked(s, "external_fd", hContext, hDevice, *pptr, size, nullptr,
                                 dmabufInode(static_cast<uint64_t>(importFd->fd)));
        } else {
            insertAllocLocked(s, *pptr, size, resolveDeviceLocked(s, hDevice));
        }
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeMemAllocHostEpilogue(
        ze_context_handle_t, const ze_host_mem_alloc_desc_t *, size_t size, size_t, void **pptr, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !pptr || !*pptr)
            return ZE_RESULT_SUCCESS;
        auto &s = state();
        std::lock_guard<std::mutex> lock(s.mtx);
        insertAllocLocked(s, *pptr, size, "host");
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeMemAllocSharedEpilogue(
        ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t *device_desc, const ze_host_mem_alloc_desc_t *,
        size_t size, size_t, ze_device_handle_t hDevice, void **pptr, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !pptr || !*pptr)
            return ZE_RESULT_SUCCESS;
        auto &s = state();
        std::lock_guard<std::mutex> lock(s.mtx);
        auto importFd = device_desc ? findImportFd(device_desc->pNext) : nullptr;
        if (importFd) {
            registerImportLocked(s, "external_fd", hContext, hDevice, *pptr, size, nullptr,
                                 dmabufInode(static_cast<uint64_t>(importFd->fd)));
        } else {
            // Shared memory with no device affinity is attributed to the host.
            insertAllocLocked(s, *pptr, size, resolveDeviceLocked(s, hDevice));
        }
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeMemFreeEpilogue(
        ze_context_handle_t, void *ptr, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !ptr)
            return ZE_RESULT_SUCCESS;
        auto &s = state();
        std::lock_guard<std::mutex> lock(s.mtx);
        eraseAllocLocked(s, ptr);
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeMemFreeExtEpilogue(
        ze_context_handle_t, const ze_memory_free_ext_desc_t *, void *ptr, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !ptr)
            return ZE_RESULT_SUCCESS;
        auto &s = state();
        std::lock_guard<std::mutex> lock(s.mtx);
        eraseAllocLocked(s, ptr);
        return ZE_RESULT_SUCCESS;
    }

    ///////////////////////////////////////////////////////////////////////////
    // IPC

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeMemGetIpcHandleEpilogue(
        ze_context_handle_t hContext, const void *ptr, ze_ipc_mem_handle_t *pIpcHandle, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !pIpcHandle)
            return ZE_RESULT_SUCCESS;
        auto &s = state();
        std::lock_guard<std::mutex> lock(s.mtx);
        recordExportLocked(s, hContext, ptr, *pIpcHandle);
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeMemGetIpcHandleWithPropertiesEpilogue(
        ze_context_handle_t hContext, const void *ptr, void *, ze_ipc_mem_handle_t *pIpcHandle, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !pIpcHandle)
            return ZE_RESULT_SUCCESS;
        auto &s = state();
        std::lock_guard<std::mutex> lock(s.mtx);
        recordExportLocked(s, hContext, ptr, *pIpcHandle);
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeMemOpenIpcHandleEpilogue(
        ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t,
        void **pptr, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !pptr || !*pptr)
            return ZE_RESULT_SUCCESS;
        auto &s = state();
        std::lock_guard<std::mutex> lock(s.mtx);
        // The descriptor inside the handle may belong to the exporter (pidfd
        // based IPC); dmabufInode() only trusts it if it is a dma-buf here, and
        // the viewer prefers the exact handle hash over the inode when joining.
        registerImportLocked(s, "ipc", hContext, hDevice, *pptr, 0, &handle, ipcHandleDmabufInode(hContext, handle));
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeMemCloseIpcHandleEpilogue(
        ze_context_handle_t, const void *ptr, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !ptr)
            return ZE_RESULT_SUCCESS;
        auto &s = state();
        std::lock_guard<std::mutex> lock(s.mtx);
        auto it = s.importIdByPtr.find(reinterpret_cast<uintptr_t>(ptr));
        if (it == s.importIdByPtr.end())
            return ZE_RESULT_SUCCESS;
        uint64_t id = it->second;
        s.importIdByPtr.erase(it);
        if (auto alloc = findAllocLocked(s, ptr))
            eraseAllocLocked(s, reinterpret_cast<const void *>(alloc->first));
        emitLocked(s, recordHeader(s, "ipc_close") + ",\"import_id\":" + std::to_string(id) + "}", true);
        return ZE_RESULT_SUCCESS;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Command lists

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeCommandListCreateEpilogue(
        ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t *,
        ze_command_list_handle_t *phCommandList, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phCommandList && *phCommandList)
            trackCommandList(*phCommandList, hContext, hDevice, false);
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeCommandListCreateImmediateEpilogue(
        ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t *,
        ze_command_list_handle_t *phCommandList, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phCommandList && *phCommandList)
            trackCommandList(*phCommandList, hContext, hDevice, true);
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeCommandListCreateCloneExpEpilogue(
        ze_command_list_handle_t hCommandList, ze_command_list_handle_t *phClonedCommandList, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !phClonedCommandList || !*phClonedCommandList)
            return ZE_RESULT_SUCCESS;
        auto &s = state();
        std::lock_guard<std::mutex> lock(s.mtx);
        auto it = s.cmdLists.find(hCommandList);
        if (it != s.cmdLists.end()) {
            CmdListInfo copy = it->second;
            s.cmdLists[*phClonedCommandList] = copy;
        }
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeCommandListDestroyEpilogue(
        ze_command_list_handle_t hCommandList, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS)
            return ZE_RESULT_SUCCESS;
        auto &s = state();
        std::lock_guard<std::mutex> lock(s.mtx);
        s.cmdLists.erase(hCommandList);
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeCommandListResetEpilogue(
        ze_command_list_handle_t hCommandList, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS)
            return ZE_RESULT_SUCCESS;
        auto &s = state();
        std::lock_guard<std::mutex> lock(s.mtx);
        auto it = s.cmdLists.find(hCommandList);
        if (it != s.cmdLists.end())
            it->second.recorded.clear();
        return ZE_RESULT_SUCCESS;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Data movement

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeCommandListAppendMemoryCopyEpilogue(
        ze_command_list_handle_t hCommandList, void *dstptr, const void *srcptr, size_t size, ze_event_handle_t,
        uint32_t, ze_event_handle_t *, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS)
            recordTransfer(hCommandList, dstptr, srcptr, nullptr, size, "copy");
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeCommandListAppendMemoryCopyRegionEpilogue(
        ze_command_list_handle_t hCommandList, void *dstptr, const ze_copy_region_t *, uint32_t, uint32_t,
        const void *srcptr, const ze_copy_region_t *srcRegion, uint32_t, uint32_t, ze_event_handle_t, uint32_t,
        ze_event_handle_t *, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS || !srcRegion)
            return ZE_RESULT_SUCCESS;
        // Region width is in bytes; height/depth are 0 or 1 for 1D/2D copies.
        uint64_t bytes = static_cast<uint64_t>(srcRegion->width) * (srcRegion->height ? srcRegion->height : 1) *
                         (srcRegion->depth ? srcRegion->depth : 1);
        recordTransfer(hCommandList, dstptr, srcptr, nullptr, bytes, "copy_region");
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeCommandListAppendMemoryCopyFromContextEpilogue(
        ze_command_list_handle_t hCommandList, void *dstptr, ze_context_handle_t hContextSrc, const void *srcptr,
        size_t size, ze_event_handle_t, uint32_t, ze_event_handle_t *, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS)
            recordTransfer(hCommandList, dstptr, srcptr, hContextSrc, size, "copy_from_context");
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeCommandListAppendMemoryFillEpilogue(
        ze_command_list_handle_t hCommandList, void *ptr, const void *, size_t, size_t size, ze_event_handle_t,
        uint32_t, ze_event_handle_t *, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS)
            recordTransfer(hCommandList, ptr, nullptr, nullptr, size, "fill");
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeCommandQueueExecuteCommandListsEpilogue(
        ze_command_queue_handle_t, uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists, ze_fence_handle_t,
        ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS)
            recordSubmission(numCommandLists, phCommandLists);
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t fabricTopologyChecker::ZEfabricTopologyChecker::zeCommandListImmediateAppendCommandListsExpEpilogue(
        ze_command_list_handle_t, uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists, ze_event_handle_t,
        uint32_t, ze_event_handle_t *, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS)
            recordSubmission(numCommandLists, phCommandLists);
        return ZE_RESULT_SUCCESS;
    }

} // namespace validation_layer
