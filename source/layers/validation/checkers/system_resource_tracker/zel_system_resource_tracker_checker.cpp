/*
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_system_resource_tracker_checker.cpp
 *
 */
#include "zel_system_resource_tracker_checker.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <sys/resource.h>
#include <unistd.h>
#include <cstring>
#include <mutex>
#include <chrono>
#include <thread>
#include <unordered_map>

extern validation_layer::context_t& validation_layer::context;

namespace validation_layer
{
    class system_resource_trackerChecker system_resource_tracker_checker;

    // Helper structure to hold system resource metrics
    struct SystemResourceMetrics {
        size_t vmSize = 0;        // Virtual memory size (KB)
        size_t vmRSS = 0;         // Resident set size (KB)
        size_t vmData = 0;        // Data segment size (KB)
        size_t vmPeak = 0;        // Peak virtual memory size (KB)
        size_t numThreads = 0;    // Number of threads
        size_t numFDs = 0;        // Number of open file descriptors
        
        SystemResourceMetrics operator-(const SystemResourceMetrics& other) const {
            SystemResourceMetrics diff;
            // Keep actual signed differences for accurate delta tracking
            diff.vmSize = vmSize > other.vmSize ? vmSize - other.vmSize : 0;
            diff.vmRSS = vmRSS > other.vmRSS ? vmRSS - other.vmRSS : 0;
            diff.vmData = vmData > other.vmData ? vmData - other.vmData : 0;
            diff.vmPeak = vmPeak > other.vmPeak ? vmPeak - other.vmPeak : 0;
            diff.numThreads = numThreads > other.numThreads ? numThreads - other.numThreads : 0;
            diff.numFDs = numFDs > other.numFDs ? numFDs - other.numFDs : 0;
            return diff;
        }
        
        // Get signed difference (can be negative)
        struct SignedMetrics {
            ssize_t vmSize = 0;
            ssize_t vmRSS = 0;
            ssize_t vmData = 0;
            ssize_t vmPeak = 0;
            ssize_t numThreads = 0;
            ssize_t numFDs = 0;
        };
        
        SignedMetrics signedDiff(const SystemResourceMetrics& other) const {
            SignedMetrics diff;
            diff.vmSize = static_cast<ssize_t>(vmSize) - static_cast<ssize_t>(other.vmSize);
            diff.vmRSS = static_cast<ssize_t>(vmRSS) - static_cast<ssize_t>(other.vmRSS);
            diff.vmData = static_cast<ssize_t>(vmData) - static_cast<ssize_t>(other.vmData);
            diff.vmPeak = static_cast<ssize_t>(vmPeak) - static_cast<ssize_t>(other.vmPeak);
            diff.numThreads = static_cast<ssize_t>(numThreads) - static_cast<ssize_t>(other.numThreads);
            diff.numFDs = static_cast<ssize_t>(numFDs) - static_cast<ssize_t>(other.numFDs);
            return diff;
        }

        SystemResourceMetrics operator+(const SystemResourceMetrics& other) const {
            SystemResourceMetrics sum;
            sum.vmSize = vmSize + other.vmSize;
            sum.vmRSS = vmRSS + other.vmRSS;
            sum.vmData = vmData + other.vmData;
            sum.vmPeak = vmPeak + other.vmPeak;
            sum.numThreads = numThreads + other.numThreads;
            sum.numFDs = numFDs + other.numFDs;
            return sum;
        }

        SystemResourceMetrics& operator+=(const SystemResourceMetrics& other) {
            vmSize += other.vmSize;
            vmRSS += other.vmRSS;
            vmData += other.vmData;
            vmPeak += other.vmPeak;
            numThreads += other.numThreads;
            numFDs += other.numFDs;
            return *this;
        }
    };

    // Structure to track resource usage by L0 resource type
    struct ResourceTracker {
        SystemResourceMetrics baseline;
        SystemResourceMetrics contexts;
        SystemResourceMetrics commandQueues;
        SystemResourceMetrics modules;
        SystemResourceMetrics kernels;
        SystemResourceMetrics eventPools;
        SystemResourceMetrics commandLists;
        SystemResourceMetrics events;
        SystemResourceMetrics fences;
        SystemResourceMetrics images;
        SystemResourceMetrics samplers;
        SystemResourceMetrics memoryAllocations;
        
        size_t contextCount = 0;
        size_t commandQueueCount = 0;
        size_t moduleCount = 0;
        size_t kernelCount = 0;
        size_t eventPoolCount = 0;
        size_t commandListCount = 0;
        size_t eventCount = 0;
        size_t fenceCount = 0;
        size_t imageCount = 0;
        size_t samplerCount = 0;
        size_t totalMemoryAllocated = 0;  // in bytes

        std::mutex trackerMutex;
        std::ofstream* csvFile = nullptr;
        bool csvEnabled = false;
        uint64_t callCounter = 0;
        std::chrono::time_point<std::chrono::steady_clock> startTime;
        
        // Pre-call metrics storage for CommandListAppend operations
        std::unordered_map<std::thread::id, SystemResourceMetrics> appendCallPreMetrics;
        
        // Handle-to-metrics maps for leak detection on destroy
        std::unordered_map<void*, SystemResourceMetrics> contextMetrics;
        std::unordered_map<void*, SystemResourceMetrics> commandQueueMetrics;
        std::unordered_map<void*, SystemResourceMetrics> moduleMetrics;
        std::unordered_map<void*, SystemResourceMetrics> kernelMetrics;
        std::unordered_map<void*, SystemResourceMetrics> eventPoolMetrics;
        std::unordered_map<void*, SystemResourceMetrics> commandListMetrics;
        std::unordered_map<void*, SystemResourceMetrics> eventMetrics;
        std::unordered_map<void*, SystemResourceMetrics> fenceMetrics;
        std::unordered_map<void*, SystemResourceMetrics> imageMetrics;
        std::unordered_map<void*, SystemResourceMetrics> samplerMetrics;
        std::unordered_map<void*, std::pair<SystemResourceMetrics, size_t>> memoryMetrics; // metrics + size
        
        // Cumulative leak tracking per resource type
        size_t totalContextLeaks = 0;
        size_t totalCommandQueueLeaks = 0;
        size_t totalModuleLeaks = 0;
        size_t totalKernelLeaks = 0;
        size_t totalEventPoolLeaks = 0;
        size_t totalCommandListLeaks = 0;
        size_t totalEventLeaks = 0;
        size_t totalFenceLeaks = 0;
        size_t totalImageLeaks = 0;
        size_t totalSamplerLeaks = 0;
        size_t totalMemoryLeaks = 0;
    };

    static ResourceTracker& getResourceTracker() {
        static ResourceTracker instance;
        return instance;
    }

    // Forward declarations
    static SystemResourceMetrics getSystemResourceMetrics();
    static void writeCsvData(const std::string& apiCall, const SystemResourceMetrics& current, const SystemResourceMetrics& delta, bool checkLeak);

    // Helper function to read system resource metrics from /proc/self/status
    static SystemResourceMetrics getSystemResourceMetrics() {
        SystemResourceMetrics metrics;
        
        std::ifstream statusFile("/proc/self/status");
        if (!statusFile.is_open()) {
            return metrics;
        }
        
        std::string line;
        while (std::getline(statusFile, line)) {
            if (line.find("VmSize:") == 0) {
                std::istringstream iss(line.substr(7));
                iss >> metrics.vmSize;
            } else if (line.find("VmRSS:") == 0) {
                std::istringstream iss(line.substr(6));
                iss >> metrics.vmRSS;
            } else if (line.find("VmData:") == 0) {
                std::istringstream iss(line.substr(7));
                iss >> metrics.vmData;
            } else if (line.find("VmPeak:") == 0) {
                std::istringstream iss(line.substr(7));
                iss >> metrics.vmPeak;
            } else if (line.find("Threads:") == 0) {
                std::istringstream iss(line.substr(8));
                iss >> metrics.numThreads;
            }
        }
        statusFile.close();
        
        // Count open file descriptors
        std::string fdPath = "/proc/self/fd";
        metrics.numFDs = 0;
        std::ifstream fdDir(fdPath);
        if (fdDir.is_open()) {
            // This is a simplified count; in reality we'd need to iterate the directory
            // For now, we'll use getrlimit as an approximation
            struct rlimit rlim;
            if (getrlimit(RLIMIT_NOFILE, &rlim) == 0) {
                metrics.numFDs = rlim.rlim_cur;
            }
        }
        
        return metrics;
    }

    // Helper function to write CSV data with signed deltas (assumes mutex is already held by caller)
    static void writeCsvData(const std::string& apiCall, const SystemResourceMetrics& current, const SystemResourceMetrics& delta, bool checkLeak = false) {
        if (!getResourceTracker().csvEnabled || !getResourceTracker().csvFile || !getResourceTracker().csvFile->is_open()) {
            context.logger->log_debug("writeCsvData skipped: csvEnabled=" + std::string(getResourceTracker().csvEnabled ? "true" : "false") + 
                                     ", csvFile=" + std::string(getResourceTracker().csvFile ? "not-null" : "null") +
                                     ", is_open=" + std::string((getResourceTracker().csvFile && getResourceTracker().csvFile->is_open()) ? "true" : "false") +
                                     ", resourceTracker@" + std::to_string(reinterpret_cast<uintptr_t>(&getResourceTracker())));
            return;
        }
        context.logger->log_debug("writeCsvData writing: " + apiCall + ", resourceTracker@" + std::to_string(reinterpret_cast<uintptr_t>(&getResourceTracker())));
        
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - getResourceTracker().startTime).count();
        
        // Build the CSV line as a string first to ensure atomic write
        std::ostringstream csvLine;
        csvLine << getResourceTracker().callCounter << ","
                << elapsed << ","
                << apiCall << ","
                << current.vmSize << ","
                << current.vmRSS << ","
                << current.vmData << ","
                << current.vmPeak << ","
                << current.numThreads << ","
                << delta.vmSize << ","
                << delta.vmRSS << ","
                << delta.vmData << ","
                << getResourceTracker().contextCount << ","
                << getResourceTracker().commandQueueCount << ","
                << getResourceTracker().moduleCount << ","
                << getResourceTracker().kernelCount << ","
                << getResourceTracker().eventPoolCount << ","
                << getResourceTracker().commandListCount << ","
                << getResourceTracker().eventCount << ","
                << getResourceTracker().fenceCount << ","
                << getResourceTracker().imageCount << ","
                << getResourceTracker().samplerCount << ","
                << getResourceTracker().totalMemoryAllocated << "\n";
        
        // Write the complete line atomically
        (*getResourceTracker().csvFile) << csvLine.str();
        getResourceTracker().csvFile->flush();
        getResourceTracker().callCounter++;
        
        // Check for memory leaks in Append operations
        if (checkLeak && (delta.vmRSS > 1024 || delta.vmSize > 1024)) {  // Leak threshold: 1MB
            std::ostringstream leakMsg;
            leakMsg << "MEMORY LEAK DETECTED in " << apiCall 
                    << ": VmRSS increased by " << delta.vmRSS << "KB, VmSize increased by " << delta.vmSize << "KB";
            context.logger->log_warning(leakMsg.str());
        }
    }

    // Generic Prologue handler for Append operations
    static void handleAppendPrologue() {
        std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
        getResourceTracker().appendCallPreMetrics[std::this_thread::get_id()] = getSystemResourceMetrics();
    }

    // Generic Epilogue handler for Append operations with leak detection
    static void handleAppendEpilogue(const std::string& apiName, const std::string& additionalInfo = "") {
        std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
        auto threadId = std::this_thread::get_id();
        auto preIt = getResourceTracker().appendCallPreMetrics.find(threadId);
        
        if (preIt != getResourceTracker().appendCallPreMetrics.end()) {
            SystemResourceMetrics current = getSystemResourceMetrics();
            auto signedDelta = current.signedDiff(preIt->second);
            
            // Create unsigned delta for CSV output (absolute values)
            SystemResourceMetrics absDelta;
            absDelta.vmSize = std::abs(signedDelta.vmSize);
            absDelta.vmRSS = std::abs(signedDelta.vmRSS);
            absDelta.vmData = std::abs(signedDelta.vmData);
            
            context.logger->log_debug("handleAppendEpilogue BEFORE writeCsvData: csvEnabled=" + std::string(getResourceTracker().csvEnabled ? "true" : "false") +
                                    ", csvFile=" + std::string(getResourceTracker().csvFile ? "not-null" : "null"));
            writeCsvData(apiName, current, absDelta, true);
            
            std::ostringstream msg;
            msg << apiName << ": " << additionalInfo
                << (additionalInfo.empty() ? "" : ", ")
                << "Delta: VmRSS=" << (signedDelta.vmRSS >= 0 ? "+" : "") << signedDelta.vmRSS 
                << "KB, VmSize=" << (signedDelta.vmSize >= 0 ? "+" : "") << signedDelta.vmSize 
                << "KB, VmData=" << (signedDelta.vmData >= 0 ? "+" : "") << signedDelta.vmData << "KB";
            context.logger->log_debug(msg.str());
            
            getResourceTracker().appendCallPreMetrics.erase(preIt);
        }
    }

    // Helper function to detect leaks on destroy (assumes mutex is already held)
    static void checkForLeak(const std::string& resourceType, void* handle, 
                            const SystemResourceMetrics& creationMetrics, size_t& leakCounter) {
        SystemResourceMetrics current = getSystemResourceMetrics();
        auto signedDelta = current.signedDiff(creationMetrics);
        
        // A leak is detected if memory didn't decrease (or increased) after destroying a resource
        // We expect memory to decrease, so positive delta indicates a leak
        if (signedDelta.vmRSS > 0 || signedDelta.vmSize > 0) {
            leakCounter += signedDelta.vmRSS;
            std::ostringstream leakMsg;
            leakMsg << "MEMORY LEAK DETECTED: " << resourceType << " handle=" << handle
                    << " - After destroy: VmRSS=" << (signedDelta.vmRSS >= 0 ? "+" : "") << signedDelta.vmRSS 
                    << "KB, VmSize=" << (signedDelta.vmSize >= 0 ? "+" : "") << signedDelta.vmSize 
                    << "KB (Total " << resourceType << " leaks: " << leakCounter << "KB)";
            context.logger->log_warning(leakMsg.str());
        }
    }

    // Helper function to log resource summary (assumes mutex is already held by caller)
    static void logResourceSummary() {
        SystemResourceMetrics current = getSystemResourceMetrics();
        
        std::ostringstream msg;
        msg << "\n  System Use After Call:\n";
        msg << "    Total System: VmRSS=" << current.vmRSS << "KB, VmSize=" << current.vmSize 
            << "KB, VmData=" << current.vmData << "KB, Threads=" << current.numThreads << "\n";
        
        if (getResourceTracker().contextCount > 0) {
            msg << "    L0 Contexts (" << getResourceTracker().contextCount << "): VmRSS=" 
                << getResourceTracker().contexts.vmRSS << "KB, VmSize=" << getResourceTracker().contexts.vmSize 
                << "KB, VmData=" << getResourceTracker().contexts.vmData << "KB\n";
        }
        
        if (getResourceTracker().commandQueueCount > 0) {
            msg << "    L0 CommandQueues (" << getResourceTracker().commandQueueCount << "): VmRSS=" 
                << getResourceTracker().commandQueues.vmRSS << "KB, VmSize=" << getResourceTracker().commandQueues.vmSize << "KB\n";
        }
        
        if (getResourceTracker().moduleCount > 0) {
            msg << "    L0 Modules (" << getResourceTracker().moduleCount << "): VmRSS=" 
                << getResourceTracker().modules.vmRSS << "KB, VmSize=" << getResourceTracker().modules.vmSize 
                << "KB, VmData=" << getResourceTracker().modules.vmData << "KB\n";
        }
        
        if (getResourceTracker().kernelCount > 0) {
            msg << "    L0 Kernels (" << getResourceTracker().kernelCount << "): VmRSS=" 
                << getResourceTracker().kernels.vmRSS << "KB, VmSize=" << getResourceTracker().kernels.vmSize << "KB\n";
        }
        
        if (getResourceTracker().eventPoolCount > 0) {
            msg << "    L0 EventPools (" << getResourceTracker().eventPoolCount << "): VmRSS=" 
                << getResourceTracker().eventPools.vmRSS << "KB, VmSize=" << getResourceTracker().eventPools.vmSize << "KB\n";
        }
        
        if (getResourceTracker().commandListCount > 0) {
            msg << "    L0 CommandLists (" << getResourceTracker().commandListCount << "): VmRSS=" 
                << getResourceTracker().commandLists.vmRSS << "KB, VmSize=" << getResourceTracker().commandLists.vmSize << "KB\n";
        }
        
        if (getResourceTracker().eventCount > 0) {
            msg << "    L0 Events (" << getResourceTracker().eventCount << "): VmRSS=" 
                << getResourceTracker().events.vmRSS << "KB\n";
        }
        
        if (getResourceTracker().fenceCount > 0) {
            msg << "    L0 Fences (" << getResourceTracker().fenceCount << "): VmRSS=" 
                << getResourceTracker().fences.vmRSS << "KB\n";
        }
        
        if (getResourceTracker().imageCount > 0) {
            msg << "    L0 Images (" << getResourceTracker().imageCount << "): VmRSS=" 
                << getResourceTracker().images.vmRSS << "KB, VmSize=" << getResourceTracker().images.vmSize << "KB\n";
        }
        
        if (getResourceTracker().samplerCount > 0) {
            msg << "    L0 Samplers (" << getResourceTracker().samplerCount << "): VmRSS=" 
                << getResourceTracker().samplers.vmRSS << "KB\n";
        }
        
        if (getResourceTracker().totalMemoryAllocated > 0) {
            msg << "    L0 Memory Allocations (Total: " << getResourceTracker().totalMemoryAllocated 
                << " bytes / " << (getResourceTracker().totalMemoryAllocated / 1024) << " KB): VmRSS=" 
                << getResourceTracker().memoryAllocations.vmRSS << "KB, VmSize=" 
                << getResourceTracker().memoryAllocations.vmSize << "KB, VmData=" 
                << getResourceTracker().memoryAllocations.vmData << "KB";
        }
        
        context.logger->log_debug(msg.str());
    }

    system_resource_trackerChecker::system_resource_trackerChecker() {
        enablesystem_resource_tracker = getenv_tobool( "ZEL_ENABLE_SYSTEM_RESOURCE_TRACKER_CHECKER" );
        context.logger->log_info("System Resource Tracker Checker constructor called @ " + std::to_string(reinterpret_cast<uintptr_t>(this)) + 
                               ", enabled=" + std::string(enablesystem_resource_tracker ? "true" : "false"));
        if(enablesystem_resource_tracker) {
            // Capture baseline metrics
            getResourceTracker().baseline = getSystemResourceMetrics();
            getResourceTracker().startTime = std::chrono::steady_clock::now();
            context.logger->log_info("System Resource Tracker initialized with baseline metrics, resourceTracker@" + 
                                   std::to_string(reinterpret_cast<uintptr_t>(&getResourceTracker())));
            
            // Check if CSV output is requested
            const char* csvPath = getenv("ZEL_SYSTEM_RESOURCE_TRACKER_CSV");
            if (csvPath && csvPath[0] != '\0') {
                try {
                    // Create unique filename per process by appending PID
                    pid_t pid = getpid();
                    std::string uniquePath(csvPath);
                    
                    // Insert PID before file extension or at end
                    size_t dotPos = uniquePath.find_last_of('.');
                    if (dotPos != std::string::npos) {
                        uniquePath.insert(dotPos, "_pid" + std::to_string(pid));
                    } else {
                        uniquePath += "_pid" + std::to_string(pid);
                    }
                    
                    // Allocate and open the file stream
                    getResourceTracker().csvFile = new std::ofstream(uniquePath, std::ios::out | std::ios::trunc);
                    if (getResourceTracker().csvFile && getResourceTracker().csvFile->is_open() && getResourceTracker().csvFile->good()) {
                        getResourceTracker().csvEnabled = true;
                        // Write CSV header
                        (*getResourceTracker().csvFile) << "CallNumber,TimeMs,APICall,VmSize_KB,VmRSS_KB,VmData_KB,VmPeak_KB,Threads,"
                                               << "Delta_VmSize_KB,Delta_VmRSS_KB,Delta_VmData_KB,"
                                               << "Contexts,CommandQueues,Modules,Kernels,EventPools,CommandLists,"
                                               << "Events,Fences,Images,Samplers,TotalMemory_Bytes\n";
                        getResourceTracker().csvFile->flush();
                        context.logger->log_info("System Resource Tracker CSV output enabled: " + uniquePath + 
                                               " [csvEnabled=" + std::string(getResourceTracker().csvEnabled ? "true" : "false") + 
                                               ", ptr=" + std::to_string(reinterpret_cast<uintptr_t>(getResourceTracker().csvFile)) + "]");
                        // Immediately verify the values are still set
                        context.logger->log_debug("POST-SET CHECK: csvEnabled=" + std::string(getResourceTracker().csvEnabled ? "true" : "false") +
                                                ", csvFile=" + std::string(getResourceTracker().csvFile ? "not-null" : "null"));
                    } else {
                        context.logger->log_error("Failed to open CSV file for System Resource Tracker: " + uniquePath);
                    }
                } catch (const std::exception& e) {
                    context.logger->log_error("Exception opening CSV file: " + std::string(e.what()));
                }
            }
            
            system_resource_trackerChecker::ZEsystem_resource_trackerChecker *zeChecker = new system_resource_trackerChecker::ZEsystem_resource_trackerChecker;
            system_resource_trackerChecker::ZESsystem_resource_trackerChecker *zesChecker = new system_resource_trackerChecker::ZESsystem_resource_trackerChecker;
            system_resource_trackerChecker::ZETsystem_resource_trackerChecker *zetChecker = new system_resource_trackerChecker::ZETsystem_resource_trackerChecker;
            system_resource_tracker_checker.zeValidation = zeChecker;
            system_resource_tracker_checker.zetValidation = zetChecker;
            system_resource_tracker_checker.zesValidation = zesChecker;
            context.logger->log_info("Registering system_resource_tracker_checker @ " + std::to_string(reinterpret_cast<uintptr_t>(&system_resource_tracker_checker)));
            validation_layer::context.validationHandlers.push_back(&system_resource_tracker_checker);
            context.logger->log_info("system_resource_tracker_checker registered successfully");
        }
    }

    system_resource_trackerChecker::~system_resource_trackerChecker() {
        if(enablesystem_resource_tracker) {
            // Log final leak summary
            std::ostringstream leakSummary;
            leakSummary << "\n=== MEMORY LEAK SUMMARY ===\n";
            bool hasLeaks = false;
            
            if (getResourceTracker().totalContextLeaks > 0) {
                leakSummary << "  Context leaks: " << getResourceTracker().totalContextLeaks << " KB\n";
                hasLeaks = true;
            }
            if (getResourceTracker().totalCommandQueueLeaks > 0) {
                leakSummary << "  CommandQueue leaks: " << getResourceTracker().totalCommandQueueLeaks << " KB\n";
                hasLeaks = true;
            }
            if (getResourceTracker().totalModuleLeaks > 0) {
                leakSummary << "  Module leaks: " << getResourceTracker().totalModuleLeaks << " KB\n";
                hasLeaks = true;
            }
            if (getResourceTracker().totalKernelLeaks > 0) {
                leakSummary << "  Kernel leaks: " << getResourceTracker().totalKernelLeaks << " KB\n";
                hasLeaks = true;
            }
            if (getResourceTracker().totalEventPoolLeaks > 0) {
                leakSummary << "  EventPool leaks: " << getResourceTracker().totalEventPoolLeaks << " KB\n";
                hasLeaks = true;
            }
            if (getResourceTracker().totalCommandListLeaks > 0) {
                leakSummary << "  CommandList leaks: " << getResourceTracker().totalCommandListLeaks << " KB\n";
                hasLeaks = true;
            }
            if (getResourceTracker().totalEventLeaks > 0) {
                leakSummary << "  Event leaks: " << getResourceTracker().totalEventLeaks << " KB\n";
                hasLeaks = true;
            }
            if (getResourceTracker().totalFenceLeaks > 0) {
                leakSummary << "  Fence leaks: " << getResourceTracker().totalFenceLeaks << " KB\n";
                hasLeaks = true;
            }
            if (getResourceTracker().totalImageLeaks > 0) {
                leakSummary << "  Image leaks: " << getResourceTracker().totalImageLeaks << " KB\n";
                hasLeaks = true;
            }
            if (getResourceTracker().totalSamplerLeaks > 0) {
                leakSummary << "  Sampler leaks: " << getResourceTracker().totalSamplerLeaks << " KB\n";
                hasLeaks = true;
            }
            if (getResourceTracker().totalMemoryLeaks > 0) {
                leakSummary << "  Memory allocation leaks: " << getResourceTracker().totalMemoryLeaks << " KB\n";
                hasLeaks = true;
            }
            
            if (hasLeaks) {
                size_t totalLeaks = getResourceTracker().totalContextLeaks + getResourceTracker().totalCommandQueueLeaks + 
                                   getResourceTracker().totalModuleLeaks + getResourceTracker().totalKernelLeaks +
                                   getResourceTracker().totalEventPoolLeaks + getResourceTracker().totalCommandListLeaks +
                                   getResourceTracker().totalEventLeaks + getResourceTracker().totalFenceLeaks +
                                   getResourceTracker().totalImageLeaks + getResourceTracker().totalSamplerLeaks +
                                   getResourceTracker().totalMemoryLeaks;
                leakSummary << "  TOTAL LEAKS: " << totalLeaks << " KB\n";
                leakSummary << "===========================";
                context.logger->log_error(leakSummary.str());
            } else {
                leakSummary << "  No memory leaks detected!\n";
                leakSummary << "===========================";
                context.logger->log_info(leakSummary.str());
            }
            
            if (getResourceTracker().csvEnabled && getResourceTracker().csvFile && getResourceTracker().csvFile->is_open()) {
                getResourceTracker().csvFile->close();
                delete getResourceTracker().csvFile;
                getResourceTracker().csvFile = nullptr;
                context.logger->log_info("System Resource Tracker CSV file closed");
            }
            delete system_resource_tracker_checker.zeValidation;
            delete system_resource_tracker_checker.zetValidation;
            delete system_resource_tracker_checker.zesValidation;
        }
    }

    // Context tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeContextCreatePrologue(ze_driver_handle_t hDriver, 
                                                                          const ze_context_desc_t *desc, 
                                                                          ze_context_handle_t *phContext) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeContextCreateEpilogue(ze_driver_handle_t hDriver, 
                                                                          const ze_context_desc_t *desc, 
                                                                          ze_context_handle_t *phContext, 
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phContext && *phContext) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().contextCount++;
                // Store creation metrics for leak detection
                getResourceTracker().contextMetrics[*phContext] = getSystemResourceMetrics();
            }
            std::ostringstream info;
            info << "Context Count=" << getResourceTracker().contextCount << ", handle=" << *phContext;
            handleAppendEpilogue("zeContextCreate", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeContextDestroyPrologue(ze_context_handle_t hContext) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeContextDestroyEpilogue(ze_context_handle_t hContext, 
                                                                           ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                if (getResourceTracker().contextCount > 0) getResourceTracker().contextCount--;
                
                // Check for leak
                auto it = getResourceTracker().contextMetrics.find(hContext);
                if (it != getResourceTracker().contextMetrics.end()) {
                    checkForLeak("Context", hContext, it->second, getResourceTracker().totalContextLeaks);
                    getResourceTracker().contextMetrics.erase(it);
                }
            }
            std::ostringstream info;
            info << "Context Count=" << getResourceTracker().contextCount << ", handle=" << hContext;
            handleAppendEpilogue("zeContextDestroy", info.str());
            logResourceSummary();
        }
        return result;
    }

    // Command Queue tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandQueueCreatePrologue(ze_context_handle_t hContext, 
                                                                               ze_device_handle_t hDevice, 
                                                                               const ze_command_queue_desc_t *desc, 
                                                                               ze_command_queue_handle_t *phCommandQueue) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandQueueCreateEpilogue(ze_context_handle_t hContext, 
                                                                               ze_device_handle_t hDevice, 
                                                                               const ze_command_queue_desc_t *desc, 
                                                                               ze_command_queue_handle_t *phCommandQueue, 
                                                                               ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phCommandQueue && *phCommandQueue) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().commandQueueCount++;
                getResourceTracker().commandQueueMetrics[*phCommandQueue] = getSystemResourceMetrics();
            }
            std::ostringstream info;
            info << "CommandQueue Count=" << getResourceTracker().commandQueueCount << ", handle=" << *phCommandQueue;
            handleAppendEpilogue("zeCommandQueueCreate", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandQueueDestroyPrologue(ze_command_queue_handle_t hCommandQueue) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandQueueDestroyEpilogue(ze_command_queue_handle_t hCommandQueue, 
                                                                                ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                if (getResourceTracker().commandQueueCount > 0) getResourceTracker().commandQueueCount--;
                
                auto it = getResourceTracker().commandQueueMetrics.find(hCommandQueue);
                if (it != getResourceTracker().commandQueueMetrics.end()) {
                    checkForLeak("CommandQueue", hCommandQueue, it->second, getResourceTracker().totalCommandQueueLeaks);
                    getResourceTracker().commandQueueMetrics.erase(it);
                }
            }
            std::ostringstream info;
            info << "CommandQueue Count=" << getResourceTracker().commandQueueCount << ", handle=" << hCommandQueue;
            handleAppendEpilogue("zeCommandQueueDestroy", info.str());
            logResourceSummary();
        }
        return result;
    }

    // Module tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeModuleCreatePrologue(ze_context_handle_t hContext, 
                                                                         ze_device_handle_t hDevice, 
                                                                         const ze_module_desc_t *desc, 
                                                                         ze_module_handle_t *phModule, 
                                                                         ze_module_build_log_handle_t *phBuildLog) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeModuleCreateEpilogue(ze_context_handle_t hContext, 
                                                                         ze_device_handle_t hDevice, 
                                                                         const ze_module_desc_t *desc, 
                                                                         ze_module_handle_t *phModule, 
                                                                         ze_module_build_log_handle_t *phBuildLog, 
                                                                         ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phModule && *phModule) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().moduleCount++;
                getResourceTracker().moduleMetrics[*phModule] = getSystemResourceMetrics();
            }
            std::ostringstream info;
            info << "Module Count=" << getResourceTracker().moduleCount << ", handle=" << *phModule;
            handleAppendEpilogue("zeModuleCreate", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeModuleDestroyPrologue(ze_module_handle_t hModule) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeModuleDestroyEpilogue(ze_module_handle_t hModule, 
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                if (getResourceTracker().moduleCount > 0) getResourceTracker().moduleCount--;
                
                auto it = getResourceTracker().moduleMetrics.find(hModule);
                if (it != getResourceTracker().moduleMetrics.end()) {
                    checkForLeak("Module", hModule, it->second, getResourceTracker().totalModuleLeaks);
                    getResourceTracker().moduleMetrics.erase(it);
                }
            }
            std::ostringstream info;
            info << "Module Count=" << getResourceTracker().moduleCount << ", handle=" << hModule;
            handleAppendEpilogue("zeModuleDestroy", info.str());
            logResourceSummary();
        }
        return result;
    }

    // Kernel tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeKernelCreatePrologue(ze_module_handle_t hModule, 
                                                                         const ze_kernel_desc_t *desc, 
                                                                         ze_kernel_handle_t *phKernel) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeKernelCreateEpilogue(ze_module_handle_t hModule, 
                                                                         const ze_kernel_desc_t *desc, 
                                                                         ze_kernel_handle_t *phKernel, 
                                                                         ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phKernel && *phKernel) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().kernelCount++;
                getResourceTracker().kernelMetrics[*phKernel] = getSystemResourceMetrics();
            }
            std::ostringstream info;
            info << "Kernel Count=" << getResourceTracker().kernelCount << ", handle=" << *phKernel;
            handleAppendEpilogue("zeKernelCreate", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeKernelDestroyPrologue(ze_kernel_handle_t hKernel) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeKernelDestroyEpilogue(ze_kernel_handle_t hKernel, 
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                if (getResourceTracker().kernelCount > 0) getResourceTracker().kernelCount--;
                
                auto it = getResourceTracker().kernelMetrics.find(hKernel);
                if (it != getResourceTracker().kernelMetrics.end()) {
                    checkForLeak("Kernel", hKernel, it->second, getResourceTracker().totalKernelLeaks);
                    getResourceTracker().kernelMetrics.erase(it);
                }
            }
            std::ostringstream info;
            info << "Kernel Count=" << getResourceTracker().kernelCount << ", handle=" << hKernel;
            handleAppendEpilogue("zeKernelDestroy", info.str());
            logResourceSummary();
        }
        return result;
    }

    // Event Pool tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeEventPoolCreatePrologue(ze_context_handle_t hContext, 
                                                                            const ze_event_pool_desc_t *desc, 
                                                                            uint32_t numDevices, 
                                                                            ze_device_handle_t *phDevices, 
                                                                            ze_event_pool_handle_t *phEventPool) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeEventPoolCreateEpilogue(ze_context_handle_t hContext, 
                                                                            const ze_event_pool_desc_t *desc, 
                                                                            uint32_t numDevices, 
                                                                            ze_device_handle_t *phDevices, 
                                                                            ze_event_pool_handle_t *phEventPool, 
                                                                            ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phEventPool && *phEventPool) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().eventPoolCount++;
                getResourceTracker().eventPoolMetrics[*phEventPool] = getSystemResourceMetrics();
            }
            std::ostringstream info;
            info << "EventPool Count=" << getResourceTracker().eventPoolCount << ", handle=" << *phEventPool;
            handleAppendEpilogue("zeEventPoolCreate", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeEventPoolDestroyPrologue(ze_event_pool_handle_t hEventPool) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeEventPoolDestroyEpilogue(ze_event_pool_handle_t hEventPool, 
                                                                             ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                if (getResourceTracker().eventPoolCount > 0) getResourceTracker().eventPoolCount--;
                
                auto it = getResourceTracker().eventPoolMetrics.find(hEventPool);
                if (it != getResourceTracker().eventPoolMetrics.end()) {
                    checkForLeak("EventPool", hEventPool, it->second, getResourceTracker().totalEventPoolLeaks);
                    getResourceTracker().eventPoolMetrics.erase(it);
                }
            }
            std::ostringstream info;
            info << "EventPool Count=" << getResourceTracker().eventPoolCount << ", handle=" << hEventPool;
            handleAppendEpilogue("zeEventPoolDestroy", info.str());
            logResourceSummary();
        }
        return result;
    }

    // Command List tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListCreateImmediatePrologue(ze_context_handle_t hContext, 
                                                                                       ze_device_handle_t hDevice, 
                                                                                       const ze_command_queue_desc_t *altdesc, 
                                                                                       ze_command_list_handle_t *phCommandList) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListCreateImmediateEpilogue(ze_context_handle_t hContext, 
                                                                                       ze_device_handle_t hDevice, 
                                                                                       const ze_command_queue_desc_t *altdesc, 
                                                                                       ze_command_list_handle_t *phCommandList, 
                                                                                       ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phCommandList && *phCommandList) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().commandListCount++;
                getResourceTracker().commandListMetrics[*phCommandList] = getSystemResourceMetrics();
            }
            std::ostringstream info;
            info << "CommandList Count=" << getResourceTracker().commandListCount << ", handle=" << *phCommandList;
            handleAppendEpilogue("zeCommandListCreateImmediate", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListCreatePrologue(ze_context_handle_t hContext, 
                                                                              ze_device_handle_t hDevice, 
                                                                              const ze_command_list_desc_t *desc, 
                                                                              ze_command_list_handle_t *phCommandList) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListCreateEpilogue(ze_context_handle_t hContext, 
                                                                              ze_device_handle_t hDevice, 
                                                                              const ze_command_list_desc_t *desc, 
                                                                              ze_command_list_handle_t *phCommandList, 
                                                                              ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phCommandList && *phCommandList) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().commandListCount++;
                getResourceTracker().commandListMetrics[*phCommandList] = getSystemResourceMetrics();
            }
            std::ostringstream info;
            info << "CommandList Count=" << getResourceTracker().commandListCount << ", handle=" << *phCommandList;
            handleAppendEpilogue("zeCommandListCreate", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListDestroyPrologue(ze_command_list_handle_t hCommandList) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListDestroyEpilogue(ze_command_list_handle_t hCommandList, 
                                                                               ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                if (getResourceTracker().commandListCount > 0) getResourceTracker().commandListCount--;
                
                auto it = getResourceTracker().commandListMetrics.find(hCommandList);
                if (it != getResourceTracker().commandListMetrics.end()) {
                    checkForLeak("CommandList", hCommandList, it->second, getResourceTracker().totalCommandListLeaks);
                    getResourceTracker().commandListMetrics.erase(it);
                }
            }
            std::ostringstream info;
            info << "CommandList Count=" << getResourceTracker().commandListCount << ", handle=" << hCommandList;
            handleAppendEpilogue("zeCommandListDestroy", info.str());
            logResourceSummary();
        }
        return result;
    }

    // Event tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeEventCreatePrologue(ze_event_pool_handle_t hEventPool, 
                                                                        const ze_event_desc_t *desc, 
                                                                        ze_event_handle_t *phEvent) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeEventCreateEpilogue(ze_event_pool_handle_t hEventPool, 
                                                                        const ze_event_desc_t *desc, 
                                                                        ze_event_handle_t *phEvent, 
                                                                        ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phEvent && *phEvent) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().eventCount++;
                getResourceTracker().eventMetrics[*phEvent] = getSystemResourceMetrics();
            }
            std::ostringstream info;
            info << "Event Count=" << getResourceTracker().eventCount << ", handle=" << *phEvent;
            handleAppendEpilogue("zeEventCreate", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeEventDestroyPrologue(ze_event_handle_t hEvent) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeEventDestroyEpilogue(ze_event_handle_t hEvent, 
                                                                         ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                if (getResourceTracker().eventCount > 0) getResourceTracker().eventCount--;
                
                auto it = getResourceTracker().eventMetrics.find(hEvent);
                if (it != getResourceTracker().eventMetrics.end()) {
                    checkForLeak("Event", hEvent, it->second, getResourceTracker().totalEventLeaks);
                    getResourceTracker().eventMetrics.erase(it);
                }
            }
            std::ostringstream info;
            info << "Event Count=" << getResourceTracker().eventCount << ", handle=" << hEvent;
            handleAppendEpilogue("zeEventDestroy", info.str());
            logResourceSummary();
        }
        return result;
    }

    // Fence tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeFenceCreatePrologue(ze_command_queue_handle_t hCommandQueue, 
                                                                        const ze_fence_desc_t *desc, 
                                                                        ze_fence_handle_t *phFence) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeFenceCreateEpilogue(ze_command_queue_handle_t hCommandQueue, 
                                                                        const ze_fence_desc_t *desc, 
                                                                        ze_fence_handle_t *phFence, 
                                                                        ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phFence && *phFence) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().fenceCount++;
                getResourceTracker().fenceMetrics[*phFence] = getSystemResourceMetrics();
            }
            std::ostringstream info;
            info << "Fence Count=" << getResourceTracker().fenceCount << ", handle=" << *phFence;
            handleAppendEpilogue("zeFenceCreate", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeFenceDestroyPrologue(ze_fence_handle_t hFence) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeFenceDestroyEpilogue(ze_fence_handle_t hFence, 
                                                                         ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                if (getResourceTracker().fenceCount > 0) getResourceTracker().fenceCount--;
                
                auto it = getResourceTracker().fenceMetrics.find(hFence);
                if (it != getResourceTracker().fenceMetrics.end()) {
                    checkForLeak("Fence", hFence, it->second, getResourceTracker().totalFenceLeaks);
                    getResourceTracker().fenceMetrics.erase(it);
                }
            }
            std::ostringstream info;
            info << "Fence Count=" << getResourceTracker().fenceCount << ", handle=" << hFence;
            handleAppendEpilogue("zeFenceDestroy", info.str());
            logResourceSummary();
        }
        return result;
    }

    // Image tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeImageCreatePrologue(ze_context_handle_t hContext, 
                                                                        ze_device_handle_t hDevice, 
                                                                        const ze_image_desc_t *desc, 
                                                                        ze_image_handle_t *phImage) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeImageCreateEpilogue(ze_context_handle_t hContext, 
                                                                        ze_device_handle_t hDevice, 
                                                                        const ze_image_desc_t *desc, 
                                                                        ze_image_handle_t *phImage, 
                                                                        ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phImage && *phImage) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().imageCount++;
                getResourceTracker().imageMetrics[*phImage] = getSystemResourceMetrics();
            }
            std::ostringstream info;
            info << "Image Count=" << getResourceTracker().imageCount << ", handle=" << *phImage;
            handleAppendEpilogue("zeImageCreate", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeImageViewCreateExtPrologue(ze_context_handle_t hContext, 
                                                                               ze_device_handle_t hDevice, 
                                                                               const ze_image_desc_t *desc, 
                                                                               ze_image_handle_t hImage, 
                                                                               ze_image_handle_t *phImageView) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeImageViewCreateExtEpilogue(ze_context_handle_t hContext, 
                                                                               ze_device_handle_t hDevice, 
                                                                               const ze_image_desc_t *desc, 
                                                                               ze_image_handle_t hImage, 
                                                                               ze_image_handle_t *phImageView, 
                                                                               ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phImageView && *phImageView) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().imageCount++;
                getResourceTracker().imageMetrics[*phImageView] = getSystemResourceMetrics();
            }
            std::ostringstream info;
            info << "Image Count=" << getResourceTracker().imageCount << ", handle=" << *phImageView;
            handleAppendEpilogue("zeImageViewCreateExt", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeImageDestroyPrologue(ze_image_handle_t hImage) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeImageDestroyEpilogue(ze_image_handle_t hImage, 
                                                                         ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                if (getResourceTracker().imageCount > 0) getResourceTracker().imageCount--;
                
                auto it = getResourceTracker().imageMetrics.find(hImage);
                if (it != getResourceTracker().imageMetrics.end()) {
                    checkForLeak("Image", hImage, it->second, getResourceTracker().totalImageLeaks);
                    getResourceTracker().imageMetrics.erase(it);
                }
            }
            std::ostringstream info;
            info << "Image Count=" << getResourceTracker().imageCount << ", handle=" << hImage;
            handleAppendEpilogue("zeImageDestroy", info.str());
            logResourceSummary();
        }
        return result;
    }

    // Sampler tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeSamplerCreatePrologue(ze_context_handle_t hContext, 
                                                                          ze_device_handle_t hDevice, 
                                                                          const ze_sampler_desc_t *desc, 
                                                                          ze_sampler_handle_t *phSampler) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeSamplerCreateEpilogue(ze_context_handle_t hContext, 
                                                                          ze_device_handle_t hDevice, 
                                                                          const ze_sampler_desc_t *desc, 
                                                                          ze_sampler_handle_t *phSampler, 
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && phSampler && *phSampler) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().samplerCount++;
                getResourceTracker().samplerMetrics[*phSampler] = getSystemResourceMetrics();
            }
            std::ostringstream info;
            info << "Sampler Count=" << getResourceTracker().samplerCount << ", handle=" << *phSampler;
            handleAppendEpilogue("zeSamplerCreate", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeSamplerDestroyPrologue(ze_sampler_handle_t hSampler) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeSamplerDestroyEpilogue(ze_sampler_handle_t hSampler, 
                                                                           ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                if (getResourceTracker().samplerCount > 0) getResourceTracker().samplerCount--;
                
                auto it = getResourceTracker().samplerMetrics.find(hSampler);
                if (it != getResourceTracker().samplerMetrics.end()) {
                    checkForLeak("Sampler", hSampler, it->second, getResourceTracker().totalSamplerLeaks);
                    getResourceTracker().samplerMetrics.erase(it);
                }
            }
            std::ostringstream info;
            info << "Sampler Count=" << getResourceTracker().samplerCount << ", handle=" << hSampler;
            handleAppendEpilogue("zeSamplerDestroy", info.str());
            logResourceSummary();
        }
        return result;
    }

    // Memory allocation tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemAllocDevicePrologue(ze_context_handle_t hContext, 
                                                                           const ze_device_mem_alloc_desc_t *device_desc, 
                                                                           size_t size, 
                                                                           size_t alignment, 
                                                                           ze_device_handle_t hDevice, 
                                                                           void **pptr) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemAllocDeviceEpilogue(ze_context_handle_t hContext, 
                                                                           const ze_device_mem_alloc_desc_t *device_desc, 
                                                                           size_t size, 
                                                                           size_t alignment, 
                                                                           ze_device_handle_t hDevice, 
                                                                           void **pptr, 
                                                                           ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && pptr && *pptr) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().totalMemoryAllocated += size;
                getResourceTracker().memoryMetrics[*pptr] = std::make_pair(getSystemResourceMetrics(), size);
            }
            std::ostringstream info;
            info << "Size=" << size << " bytes (" << (size / 1024) << " KB), Total=" << getResourceTracker().totalMemoryAllocated << ", ptr=" << *pptr;
            handleAppendEpilogue("zeMemAllocDevice", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemAllocHostPrologue(ze_context_handle_t hContext, 
                                                                         const ze_host_mem_alloc_desc_t *host_desc, 
                                                                         size_t size, 
                                                                         size_t alignment, 
                                                                         void **pptr) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemAllocHostEpilogue(ze_context_handle_t hContext, 
                                                                         const ze_host_mem_alloc_desc_t *host_desc, 
                                                                         size_t size, 
                                                                         size_t alignment, 
                                                                         void **pptr, 
                                                                         ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && pptr && *pptr) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().totalMemoryAllocated += size;
                getResourceTracker().memoryMetrics[*pptr] = std::make_pair(getSystemResourceMetrics(), size);
            }
            std::ostringstream info;
            info << "Size=" << size << " bytes (" << (size / 1024) << " KB), Total=" << getResourceTracker().totalMemoryAllocated << ", ptr=" << *pptr;
            handleAppendEpilogue("zeMemAllocHost", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemAllocSharedPrologue(ze_context_handle_t hContext, 
                                                                           const ze_device_mem_alloc_desc_t *device_desc, 
                                                                           const ze_host_mem_alloc_desc_t *host_desc, 
                                                                           size_t size, 
                                                                           size_t alignment, 
                                                                           ze_device_handle_t hDevice, 
                                                                           void **pptr) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemAllocSharedEpilogue(ze_context_handle_t hContext, 
                                                                           const ze_device_mem_alloc_desc_t *device_desc, 
                                                                           const ze_host_mem_alloc_desc_t *host_desc, 
                                                                           size_t size, 
                                                                           size_t alignment, 
                                                                           ze_device_handle_t hDevice, 
                                                                           void **pptr, 
                                                                           ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS && pptr && *pptr) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                getResourceTracker().totalMemoryAllocated += size;
                getResourceTracker().memoryMetrics[*pptr] = std::make_pair(getSystemResourceMetrics(), size);
            }
            std::ostringstream info;
            info << "Size=" << size << " bytes (" << (size / 1024) << " KB), Total=" << getResourceTracker().totalMemoryAllocated << ", ptr=" << *pptr;
            handleAppendEpilogue("zeMemAllocShared", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemFreePrologue(ze_context_handle_t hContext, 
                                                                    void *ptr) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemFreeEpilogue(ze_context_handle_t hContext, 
                                                                    void *ptr, 
                                                                    ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                auto it = getResourceTracker().memoryMetrics.find(ptr);
                if (it != getResourceTracker().memoryMetrics.end()) {
                    size_t freedSize = it->second.second;
                    if (getResourceTracker().totalMemoryAllocated >= freedSize) {
                        getResourceTracker().totalMemoryAllocated -= freedSize;
                    }
                    checkForLeak("Memory", ptr, it->second.first, getResourceTracker().totalMemoryLeaks);
                    getResourceTracker().memoryMetrics.erase(it);
                }
            }
            std::ostringstream info;
            info << "Total Memory=" << getResourceTracker().totalMemoryAllocated << ", ptr=" << ptr;
            handleAppendEpilogue("zeMemFree", info.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemFreeExtPrologue(ze_context_handle_t hContext, 
                                                                       const ze_memory_free_ext_desc_t *pMemFreeDesc, 
                                                                       void *ptr) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemFreeExtEpilogue(ze_context_handle_t hContext, 
                                                                       const ze_memory_free_ext_desc_t *pMemFreeDesc, 
                                                                       void *ptr, 
                                                                       ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            {
                std::lock_guard<std::mutex> lock(getResourceTracker().trackerMutex);
                auto it = getResourceTracker().memoryMetrics.find(ptr);
                if (it != getResourceTracker().memoryMetrics.end()) {
                    size_t freedSize = it->second.second;
                    if (getResourceTracker().totalMemoryAllocated >= freedSize) {
                        getResourceTracker().totalMemoryAllocated -= freedSize;
                    }
                    checkForLeak("Memory", ptr, it->second.first, getResourceTracker().totalMemoryLeaks);
                    getResourceTracker().memoryMetrics.erase(it);
                }
            }
            std::ostringstream info;
            info << "Total Memory=" << getResourceTracker().totalMemoryAllocated << ", ptr=" << ptr;
            handleAppendEpilogue("zeMemFreeExt", info.str());
            logResourceSummary();
        }
        return result;
    }

    // CommandList Append operations tracking with Prologue/Epilogue pairs
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendBarrierPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendBarrierEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "WaitEvents=" << numWaitEvents;
            handleAppendEpilogue("zeCommandListAppendBarrier", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryRangesBarrierPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          uint32_t numRanges,
                                                                          const size_t* pRangeSizes,
                                                                          const void** pRanges,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryRangesBarrierEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          uint32_t numRanges,
                                                                          const size_t* pRangeSizes,
                                                                          const void** pRanges,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "Ranges=" << numRanges;
            handleAppendEpilogue("zeCommandListAppendMemoryRangesBarrier", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryCopyPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          void* dstptr,
                                                                          const void* srcptr,
                                                                          size_t size,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryCopyEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          void* dstptr,
                                                                          const void* srcptr,
                                                                          size_t size,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "Size=" << size << " bytes (" << (size / 1024) << " KB)";
            handleAppendEpilogue("zeCommandListAppendMemoryCopy", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryFillPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          void* ptr,
                                                                          const void* pattern,
                                                                          size_t pattern_size,
                                                                          size_t size,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryFillEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          void* ptr,
                                                                          const void* pattern,
                                                                          size_t pattern_size,
                                                                          size_t size,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "Size=" << size << " bytes, PatternSize=" << pattern_size;
            handleAppendEpilogue("zeCommandListAppendMemoryFill", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryCopyRegionPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          void* dstptr,
                                                                          const ze_copy_region_t* dstRegion,
                                                                          uint32_t dstPitch,
                                                                          uint32_t dstSlicePitch,
                                                                          const void* srcptr,
                                                                          const ze_copy_region_t* srcRegion,
                                                                          uint32_t srcPitch,
                                                                          uint32_t srcSlicePitch,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryCopyRegionEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          void* dstptr,
                                                                          const ze_copy_region_t* dstRegion,
                                                                          uint32_t dstPitch,
                                                                          uint32_t dstSlicePitch,
                                                                          const void* srcptr,
                                                                          const ze_copy_region_t* srcRegion,
                                                                          uint32_t srcPitch,
                                                                          uint32_t srcSlicePitch,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "MemoryCopyRegion";
            handleAppendEpilogue("zeCommandListAppendMemoryCopyRegion", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryCopyFromContextPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          void* dstptr,
                                                                          ze_context_handle_t hContextSrc,
                                                                          const void* srcptr,
                                                                          size_t size,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryCopyFromContextEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          void* dstptr,
                                                                          ze_context_handle_t hContextSrc,
                                                                          const void* srcptr,
                                                                          size_t size,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "Size=" << size << " bytes";
            handleAppendEpilogue("zeCommandListAppendMemoryCopyFromContext", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendImageCopyPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_image_handle_t hDstImage,
                                                                          ze_image_handle_t hSrcImage,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendImageCopyEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_image_handle_t hDstImage,
                                                                          ze_image_handle_t hSrcImage,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "ImageCopy";
            handleAppendEpilogue("zeCommandListAppendImageCopy", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendImageCopyRegionPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_image_handle_t hDstImage,
                                                                          ze_image_handle_t hSrcImage,
                                                                          const ze_image_region_t* pDstRegion,
                                                                          const ze_image_region_t* pSrcRegion,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendImageCopyRegionEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_image_handle_t hDstImage,
                                                                          ze_image_handle_t hSrcImage,
                                                                          const ze_image_region_t* pDstRegion,
                                                                          const ze_image_region_t* pSrcRegion,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "ImageCopyRegion";
            handleAppendEpilogue("zeCommandListAppendImageCopyRegion", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendImageCopyToMemoryPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          void* dstptr,
                                                                          ze_image_handle_t hSrcImage,
                                                                          const ze_image_region_t* pSrcRegion,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendImageCopyToMemoryEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          void* dstptr,
                                                                          ze_image_handle_t hSrcImage,
                                                                          const ze_image_region_t* pSrcRegion,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "ImageCopyToMemory";
            handleAppendEpilogue("zeCommandListAppendImageCopyToMemory", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendImageCopyFromMemoryPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_image_handle_t hDstImage,
                                                                          const void* srcptr,
                                                                          const ze_image_region_t* pDstRegion,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendImageCopyFromMemoryEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_image_handle_t hDstImage,
                                                                          const void* srcptr,
                                                                          const ze_image_region_t* pDstRegion,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "ImageCopyFromMemory";
            handleAppendEpilogue("zeCommandListAppendImageCopyFromMemory", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryPrefetchPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          const void* ptr,
                                                                          size_t size) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryPrefetchEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          const void* ptr,
                                                                          size_t size,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "Size=" << size << " bytes";
            handleAppendEpilogue("zeCommandListAppendMemoryPrefetch", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemAdvisePrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_device_handle_t hDevice,
                                                                          const void* ptr,
                                                                          size_t size,
                                                                          ze_memory_advice_t advice) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemAdviseEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_device_handle_t hDevice,
                                                                          const void* ptr,
                                                                          size_t size,
                                                                          ze_memory_advice_t advice,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "Size=" << size << " bytes, Advice=" << advice;
            handleAppendEpilogue("zeCommandListAppendMemAdvise", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendSignalEventPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_event_handle_t hEvent) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendSignalEventEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_event_handle_t hEvent,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "SignalEvent";
            handleAppendEpilogue("zeCommandListAppendSignalEvent", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendWaitOnEventsPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          uint32_t numEvents,
                                                                          ze_event_handle_t* phEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendWaitOnEventsEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          uint32_t numEvents,
                                                                          ze_event_handle_t* phEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "NumEvents=" << numEvents;
            handleAppendEpilogue("zeCommandListAppendWaitOnEvents", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendEventResetPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_event_handle_t hEvent) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendEventResetEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_event_handle_t hEvent,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "EventReset";
            handleAppendEpilogue("zeCommandListAppendEventReset", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendQueryKernelTimestampsPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          uint32_t numEvents,
                                                                          ze_event_handle_t* phEvents,
                                                                          void* dstptr,
                                                                          const size_t* pOffsets,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendQueryKernelTimestampsEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          uint32_t numEvents,
                                                                          ze_event_handle_t* phEvents,
                                                                          void* dstptr,
                                                                          const size_t* pOffsets,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "NumEvents=" << numEvents;
            handleAppendEpilogue("zeCommandListAppendQueryKernelTimestamps", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendLaunchKernelPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_kernel_handle_t hKernel,
                                                                          const ze_group_count_t* pLaunchFuncArgs,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendLaunchKernelEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_kernel_handle_t hKernel,
                                                                          const ze_group_count_t* pLaunchFuncArgs,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            if (pLaunchFuncArgs) {
                info << "GroupCount=[" << pLaunchFuncArgs->groupCountX << "," 
                     << pLaunchFuncArgs->groupCountY << "," << pLaunchFuncArgs->groupCountZ << "]";
            }
            handleAppendEpilogue("zeCommandListAppendLaunchKernel", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendLaunchCooperativeKernelPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_kernel_handle_t hKernel,
                                                                          const ze_group_count_t* pLaunchFuncArgs,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendLaunchCooperativeKernelEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_kernel_handle_t hKernel,
                                                                          const ze_group_count_t* pLaunchFuncArgs,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "LaunchCooperativeKernel";
            handleAppendEpilogue("zeCommandListAppendLaunchCooperativeKernel", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendLaunchKernelIndirectPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_kernel_handle_t hKernel,
                                                                          const ze_group_count_t* pLaunchArgumentsBuffer,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendLaunchKernelIndirectEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_kernel_handle_t hKernel,
                                                                          const ze_group_count_t* pLaunchArgumentsBuffer,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "LaunchKernelIndirect";
            handleAppendEpilogue("zeCommandListAppendLaunchKernelIndirect", info.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendWriteGlobalTimestampPrologue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          uint64_t* dstptr,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents) {
        handleAppendPrologue();
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendWriteGlobalTimestampEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          uint64_t* dstptr,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::ostringstream info;
            info << "WriteGlobalTimestamp";
            handleAppendEpilogue("zeCommandListAppendWriteGlobalTimestamp", info.str());
        }
        return result;
    }
}