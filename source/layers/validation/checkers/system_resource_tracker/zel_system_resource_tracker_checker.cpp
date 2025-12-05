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
            diff.vmSize = vmSize > other.vmSize ? vmSize - other.vmSize : 0;
            diff.vmRSS = vmRSS > other.vmRSS ? vmRSS - other.vmRSS : 0;
            diff.vmData = vmData > other.vmData ? vmData - other.vmData : 0;
            diff.vmPeak = vmPeak > other.vmPeak ? vmPeak - other.vmPeak : 0;
            diff.numThreads = numThreads > other.numThreads ? numThreads - other.numThreads : 0;
            diff.numFDs = numFDs > other.numFDs ? numFDs - other.numFDs : 0;
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
    };

    static ResourceTracker resourceTracker;

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

    // Helper function to write CSV data (assumes mutex is already held by caller)
    static void writeCsvData(const std::string& apiCall, const SystemResourceMetrics& current, const SystemResourceMetrics& delta) {
        if (!resourceTracker.csvEnabled || !resourceTracker.csvFile || !resourceTracker.csvFile->is_open()) {
            return;
        }
        
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - resourceTracker.startTime).count();
        
        // Build the CSV line as a string first to ensure atomic write
        std::ostringstream csvLine;
        csvLine << resourceTracker.callCounter << ","
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
                << resourceTracker.contextCount << ","
                << resourceTracker.commandQueueCount << ","
                << resourceTracker.moduleCount << ","
                << resourceTracker.kernelCount << ","
                << resourceTracker.eventPoolCount << ","
                << resourceTracker.commandListCount << ","
                << resourceTracker.eventCount << ","
                << resourceTracker.fenceCount << ","
                << resourceTracker.imageCount << ","
                << resourceTracker.samplerCount << ","
                << resourceTracker.totalMemoryAllocated << "\n";
        
        // Write the complete line atomically
        (*resourceTracker.csvFile) << csvLine.str();
        resourceTracker.csvFile->flush();
        resourceTracker.callCounter++;
    }

    // Helper function to log resource summary (assumes mutex is already held by caller)
    static void logResourceSummary() {
        SystemResourceMetrics current = getSystemResourceMetrics();
        
        std::ostringstream msg;
        msg << "\n  System Use After Call:\n";
        msg << "    Total System: VmRSS=" << current.vmRSS << "KB, VmSize=" << current.vmSize 
            << "KB, VmData=" << current.vmData << "KB, Threads=" << current.numThreads << "\n";
        
        if (resourceTracker.contextCount > 0) {
            msg << "    L0 Contexts (" << resourceTracker.contextCount << "): VmRSS=" 
                << resourceTracker.contexts.vmRSS << "KB, VmSize=" << resourceTracker.contexts.vmSize 
                << "KB, VmData=" << resourceTracker.contexts.vmData << "KB\n";
        }
        
        if (resourceTracker.commandQueueCount > 0) {
            msg << "    L0 CommandQueues (" << resourceTracker.commandQueueCount << "): VmRSS=" 
                << resourceTracker.commandQueues.vmRSS << "KB, VmSize=" << resourceTracker.commandQueues.vmSize << "KB\n";
        }
        
        if (resourceTracker.moduleCount > 0) {
            msg << "    L0 Modules (" << resourceTracker.moduleCount << "): VmRSS=" 
                << resourceTracker.modules.vmRSS << "KB, VmSize=" << resourceTracker.modules.vmSize 
                << "KB, VmData=" << resourceTracker.modules.vmData << "KB\n";
        }
        
        if (resourceTracker.kernelCount > 0) {
            msg << "    L0 Kernels (" << resourceTracker.kernelCount << "): VmRSS=" 
                << resourceTracker.kernels.vmRSS << "KB, VmSize=" << resourceTracker.kernels.vmSize << "KB\n";
        }
        
        if (resourceTracker.eventPoolCount > 0) {
            msg << "    L0 EventPools (" << resourceTracker.eventPoolCount << "): VmRSS=" 
                << resourceTracker.eventPools.vmRSS << "KB, VmSize=" << resourceTracker.eventPools.vmSize << "KB\n";
        }
        
        if (resourceTracker.commandListCount > 0) {
            msg << "    L0 CommandLists (" << resourceTracker.commandListCount << "): VmRSS=" 
                << resourceTracker.commandLists.vmRSS << "KB, VmSize=" << resourceTracker.commandLists.vmSize << "KB\n";
        }
        
        if (resourceTracker.eventCount > 0) {
            msg << "    L0 Events (" << resourceTracker.eventCount << "): VmRSS=" 
                << resourceTracker.events.vmRSS << "KB\n";
        }
        
        if (resourceTracker.fenceCount > 0) {
            msg << "    L0 Fences (" << resourceTracker.fenceCount << "): VmRSS=" 
                << resourceTracker.fences.vmRSS << "KB\n";
        }
        
        if (resourceTracker.imageCount > 0) {
            msg << "    L0 Images (" << resourceTracker.imageCount << "): VmRSS=" 
                << resourceTracker.images.vmRSS << "KB, VmSize=" << resourceTracker.images.vmSize << "KB\n";
        }
        
        if (resourceTracker.samplerCount > 0) {
            msg << "    L0 Samplers (" << resourceTracker.samplerCount << "): VmRSS=" 
                << resourceTracker.samplers.vmRSS << "KB\n";
        }
        
        if (resourceTracker.totalMemoryAllocated > 0) {
            msg << "    L0 Memory Allocations (Total: " << resourceTracker.totalMemoryAllocated 
                << " bytes / " << (resourceTracker.totalMemoryAllocated / 1024) << " KB): VmRSS=" 
                << resourceTracker.memoryAllocations.vmRSS << "KB, VmSize=" 
                << resourceTracker.memoryAllocations.vmSize << "KB, VmData=" 
                << resourceTracker.memoryAllocations.vmData << "KB";
        }
        
        context.logger->log_debug(msg.str());
    }

    system_resource_trackerChecker::system_resource_trackerChecker() {
        enablesystem_resource_tracker = getenv_tobool( "ZEL_ENABLE_SYSTEM_RESOURCE_TRACKER_CHECKER" );
        if(enablesystem_resource_tracker) {
            // Capture baseline metrics
            resourceTracker.baseline = getSystemResourceMetrics();
            resourceTracker.startTime = std::chrono::steady_clock::now();
            
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
                    resourceTracker.csvFile = new std::ofstream(uniquePath, std::ios::out | std::ios::trunc);
                    if (resourceTracker.csvFile && resourceTracker.csvFile->is_open() && resourceTracker.csvFile->good()) {
                        resourceTracker.csvEnabled = true;
                        // Write CSV header
                        (*resourceTracker.csvFile) << "CallNumber,TimeMs,APICall,VmSize_KB,VmRSS_KB,VmData_KB,VmPeak_KB,Threads,"
                                               << "Delta_VmSize_KB,Delta_VmRSS_KB,Delta_VmData_KB,"
                                               << "Contexts,CommandQueues,Modules,Kernels,EventPools,CommandLists,"
                                               << "Events,Fences,Images,Samplers,TotalMemory_Bytes\n";
                        resourceTracker.csvFile->flush();
                        context.logger->log_info("System Resource Tracker CSV output enabled: " + uniquePath);
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
            validation_layer::context.validationHandlers.push_back(&system_resource_tracker_checker);
        }
    }

    system_resource_trackerChecker::~system_resource_trackerChecker() {
        if(enablesystem_resource_tracker) {
            if (resourceTracker.csvEnabled && resourceTracker.csvFile && resourceTracker.csvFile->is_open()) {
                resourceTracker.csvFile->close();
                delete resourceTracker.csvFile;
                resourceTracker.csvFile = nullptr;
                context.logger->log_info("System Resource Tracker CSV file closed");
            }
            delete system_resource_tracker_checker.zeValidation;
            delete system_resource_tracker_checker.zetValidation;
            delete system_resource_tracker_checker.zesValidation;
        }
    }

    // Context tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeContextCreateEpilogue(ze_driver_handle_t hDriver, 
                                                                          const ze_context_desc_t *desc, 
                                                                          ze_context_handle_t *phContext, 
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.contexts;
            
            resourceTracker.contextCount++;
            resourceTracker.contexts = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.contexts - prevTotal;
            
            writeCsvData("zeContextCreate", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeContextCreate: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB, VmData=" << delta.vmData 
                << "KB, Threads=" << delta.numThreads;
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeContextDestroyEpilogue(ze_context_handle_t hContext, 
                                                                           ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.contexts;
            
            if (resourceTracker.contextCount > 0) {
                resourceTracker.contextCount--;
            }
            resourceTracker.contexts = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.contexts - prevTotal;
            
            writeCsvData("zeContextDestroy", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeContextDestroy: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB, VmData=" << delta.vmData 
                << "KB, Threads=" << delta.numThreads;
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    // Command Queue tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandQueueCreateEpilogue(ze_context_handle_t hContext, 
                                                                               ze_device_handle_t hDevice, 
                                                                               const ze_command_queue_desc_t *desc, 
                                                                               ze_command_queue_handle_t *phCommandQueue, 
                                                                               ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandQueues;
            
            resourceTracker.commandQueueCount++;
            resourceTracker.commandQueues = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.commandQueues - prevTotal;
            
            writeCsvData("zeCommandQueueCreate", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeCommandQueueCreate: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB, Threads=" << delta.numThreads;
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandQueueDestroyEpilogue(ze_command_queue_handle_t hCommandQueue, 
                                                                                ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandQueues;
            
            if (resourceTracker.commandQueueCount > 0) {
                resourceTracker.commandQueueCount--;
            }
            resourceTracker.commandQueues = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.commandQueues - prevTotal;
            
            writeCsvData("zeCommandQueueDestroy", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeCommandQueueDestroy: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    // Module tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeModuleCreateEpilogue(ze_context_handle_t hContext, 
                                                                         ze_device_handle_t hDevice, 
                                                                         const ze_module_desc_t *desc, 
                                                                         ze_module_handle_t *phModule, 
                                                                         ze_module_build_log_handle_t *phBuildLog, 
                                                                         ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.modules;
            
            resourceTracker.moduleCount++;
            resourceTracker.modules = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.modules - prevTotal;
            
            writeCsvData("zeModuleCreate", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeModuleCreate: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB, VmData=" << delta.vmData << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeModuleDestroyEpilogue(ze_module_handle_t hModule, 
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.modules;
            
            if (resourceTracker.moduleCount > 0) {
                resourceTracker.moduleCount--;
            }
            resourceTracker.modules = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.modules - prevTotal;
            
            writeCsvData("zeModuleDestroy", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeModuleDestroy: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    // Kernel tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeKernelCreateEpilogue(ze_module_handle_t hModule, 
                                                                         const ze_kernel_desc_t *desc, 
                                                                         ze_kernel_handle_t *phKernel, 
                                                                         ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.kernels;
            
            resourceTracker.kernelCount++;
            resourceTracker.kernels = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.kernels - prevTotal;
            
            writeCsvData("zeKernelCreate", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeKernelCreate: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeKernelDestroyEpilogue(ze_kernel_handle_t hKernel, 
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.kernels;
            
            if (resourceTracker.kernelCount > 0) {
                resourceTracker.kernelCount--;
            }
            resourceTracker.kernels = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.kernels - prevTotal;
            
            writeCsvData("zeKernelDestroy", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeKernelDestroy: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    // Event Pool tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeEventPoolCreateEpilogue(ze_context_handle_t hContext, 
                                                                            const ze_event_pool_desc_t *desc, 
                                                                            uint32_t numDevices, 
                                                                            ze_device_handle_t *phDevices, 
                                                                            ze_event_pool_handle_t *phEventPool, 
                                                                            ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.eventPools;
            
            resourceTracker.eventPoolCount++;
            resourceTracker.eventPools = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.eventPools - prevTotal;
            
            writeCsvData("zeEventPoolCreate", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeEventPoolCreate: Count=" << (desc ? desc->count : 0)
                << ", Delta: VmRSS=" << delta.vmRSS << "KB, VmSize=" << delta.vmSize << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeEventPoolDestroyEpilogue(ze_event_pool_handle_t hEventPool, 
                                                                             ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.eventPools;
            
            if (resourceTracker.eventPoolCount > 0) {
                resourceTracker.eventPoolCount--;
            }
            resourceTracker.eventPools = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.eventPools - prevTotal;
            
            writeCsvData("zeEventPoolDestroy", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeEventPoolDestroy: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    // Command List tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListCreateImmediateEpilogue(ze_context_handle_t hContext, 
                                                                                       ze_device_handle_t hDevice, 
                                                                                       const ze_command_queue_desc_t *altdesc, 
                                                                                       ze_command_list_handle_t *phCommandList, 
                                                                                       ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandListCount++;
            resourceTracker.commandLists = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListCreateImmediate", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListCreateImmediate: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListCreateEpilogue(ze_context_handle_t hContext, 
                                                                              ze_device_handle_t hDevice, 
                                                                              const ze_command_list_desc_t *desc, 
                                                                              ze_command_list_handle_t *phCommandList, 
                                                                              ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandListCount++;
            resourceTracker.commandLists = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListCreate", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListCreate: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListDestroyEpilogue(ze_command_list_handle_t hCommandList, 
                                                                               ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            if (resourceTracker.commandListCount > 0) {
                resourceTracker.commandListCount--;
            }
            resourceTracker.commandLists = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListDestroy", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListDestroy: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    // Event tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeEventCreateEpilogue(ze_event_pool_handle_t hEventPool, 
                                                                        const ze_event_desc_t *desc, 
                                                                        ze_event_handle_t *phEvent, 
                                                                        ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.events;
            
            resourceTracker.eventCount++;
            resourceTracker.events = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.events - prevTotal;
            
            writeCsvData("zeEventCreate", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeEventCreate: Index=" << (desc ? desc->index : 0)
                << ", Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeEventDestroyEpilogue(ze_event_handle_t hEvent, 
                                                                         ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.events;
            
            if (resourceTracker.eventCount > 0) {
                resourceTracker.eventCount--;
            }
            resourceTracker.events = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.events - prevTotal;
            
            writeCsvData("zeEventDestroy", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeEventDestroy: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    // Fence tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeFenceCreateEpilogue(ze_command_queue_handle_t hCommandQueue, 
                                                                        const ze_fence_desc_t *desc, 
                                                                        ze_fence_handle_t *phFence, 
                                                                        ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.fences;
            
            resourceTracker.fenceCount++;
            resourceTracker.fences = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.fences - prevTotal;
            
            writeCsvData("zeFenceCreate", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeFenceCreate: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeFenceDestroyEpilogue(ze_fence_handle_t hFence, 
                                                                         ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.fences;
            
            if (resourceTracker.fenceCount > 0) {
                resourceTracker.fenceCount--;
            }
            resourceTracker.fences = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.fences - prevTotal;
            
            writeCsvData("zeFenceDestroy", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeFenceDestroy: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    // Image tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeImageCreateEpilogue(ze_context_handle_t hContext, 
                                                                        ze_device_handle_t hDevice, 
                                                                        const ze_image_desc_t *desc, 
                                                                        ze_image_handle_t *phImage, 
                                                                        ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.images;
            
            size_t imageSize = 0;
            if (desc) {
                imageSize = desc->width * desc->height * (desc->depth > 0 ? desc->depth : 1);
            }
            
            resourceTracker.imageCount++;
            resourceTracker.images = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.images - prevTotal;
            
            writeCsvData("zeImageCreate", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeImageCreate: Size=" << imageSize 
                << " pixels, Delta: VmRSS=" << delta.vmRSS << "KB, VmSize=" << delta.vmSize << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeImageViewCreateExtEpilogue(ze_context_handle_t hContext, 
                                                                               ze_device_handle_t hDevice, 
                                                                               const ze_image_desc_t *desc, 
                                                                               ze_image_handle_t hImage, 
                                                                               ze_image_handle_t *phImageView, 
                                                                               ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.images;
            
            resourceTracker.imageCount++;
            resourceTracker.images = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.images - prevTotal;
            
            writeCsvData("zeImageViewCreateExt", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeImageViewCreateExt: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeImageDestroyEpilogue(ze_image_handle_t hImage, 
                                                                         ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.images;
            
            if (resourceTracker.imageCount > 0) {
                resourceTracker.imageCount--;
            }
            resourceTracker.images = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.images - prevTotal;
            
            writeCsvData("zeImageDestroy", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeImageDestroy: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    // Sampler tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeSamplerCreateEpilogue(ze_context_handle_t hContext, 
                                                                          ze_device_handle_t hDevice, 
                                                                          const ze_sampler_desc_t *desc, 
                                                                          ze_sampler_handle_t *phSampler, 
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.samplers;
            
            resourceTracker.samplerCount++;
            resourceTracker.samplers = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.samplers - prevTotal;
            
            writeCsvData("zeSamplerCreate", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeSamplerCreate: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeSamplerDestroyEpilogue(ze_sampler_handle_t hSampler, 
                                                                           ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.samplers;
            
            if (resourceTracker.samplerCount > 0) {
                resourceTracker.samplerCount--;
            }
            resourceTracker.samplers = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.samplers - prevTotal;
            
            writeCsvData("zeSamplerDestroy", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeSamplerDestroy: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    // Memory allocation tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemAllocDeviceEpilogue(ze_context_handle_t hContext, 
                                                                           const ze_device_mem_alloc_desc_t *device_desc, 
                                                                           size_t size, 
                                                                           size_t alignment, 
                                                                           ze_device_handle_t hDevice, 
                                                                           void **pptr, 
                                                                           ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.memoryAllocations;
            
            resourceTracker.totalMemoryAllocated += size;
            resourceTracker.memoryAllocations = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.memoryAllocations - prevTotal;
            
            writeCsvData("zeMemAllocDevice", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeMemAllocDevice: Size=" << size 
                << " bytes (" << (size / 1024) << " KB), Alignment=" << alignment 
                << ", Delta: VmRSS=" << delta.vmRSS << "KB, VmSize=" << delta.vmSize 
                << "KB, VmData=" << delta.vmData << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemAllocHostEpilogue(ze_context_handle_t hContext, 
                                                                         const ze_host_mem_alloc_desc_t *host_desc, 
                                                                         size_t size, 
                                                                         size_t alignment, 
                                                                         void **pptr, 
                                                                         ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.memoryAllocations;
            
            resourceTracker.totalMemoryAllocated += size;
            resourceTracker.memoryAllocations = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.memoryAllocations - prevTotal;
            
            writeCsvData("zeMemAllocHost", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeMemAllocHost: Size=" << size 
                << " bytes (" << (size / 1024) << " KB), Alignment=" << alignment 
                << ", Delta: VmRSS=" << delta.vmRSS << "KB, VmSize=" << delta.vmSize 
                << "KB, VmData=" << delta.vmData << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemAllocSharedEpilogue(ze_context_handle_t hContext, 
                                                                           const ze_device_mem_alloc_desc_t *device_desc, 
                                                                           const ze_host_mem_alloc_desc_t *host_desc, 
                                                                           size_t size, 
                                                                           size_t alignment, 
                                                                           ze_device_handle_t hDevice, 
                                                                           void **pptr, 
                                                                           ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.memoryAllocations;
            
            resourceTracker.totalMemoryAllocated += size;
            resourceTracker.memoryAllocations = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.memoryAllocations - prevTotal;
            
            writeCsvData("zeMemAllocShared", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeMemAllocShared: Size=" << size 
                << " bytes (" << (size / 1024) << " KB), Alignment=" << alignment 
                << ", Delta: VmRSS=" << delta.vmRSS << "KB, VmSize=" << delta.vmSize 
                << "KB, VmData=" << delta.vmData << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemFreeEpilogue(ze_context_handle_t hContext, 
                                                                    void *ptr, 
                                                                    ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.memoryAllocations;
            
            resourceTracker.memoryAllocations = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.memoryAllocations - prevTotal;
            
            writeCsvData("zeMemFree", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeMemFree: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB, VmData=" << delta.vmData << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeMemFreeExtEpilogue(ze_context_handle_t hContext, 
                                                                       const ze_memory_free_ext_desc_t *pMemFreeDesc, 
                                                                       void *ptr, 
                                                                       ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics beforeMetrics = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.memoryAllocations;
            
            resourceTracker.memoryAllocations = beforeMetrics - resourceTracker.baseline;
            
            SystemResourceMetrics delta = resourceTracker.memoryAllocations - prevTotal;
            
            writeCsvData("zeMemFreeExt", beforeMetrics, delta);
            
            std::ostringstream msg;
            msg << "zeMemFreeExt: Delta: VmRSS=" << delta.vmRSS 
                << "KB, VmSize=" << delta.vmSize << "KB, VmData=" << delta.vmData << "KB";
            context.logger->log_debug(msg.str());
            logResourceSummary();
        }
        return result;
    }

    // CommandList Append operations tracking
    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendBarrierEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendBarrier", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendBarrier: WaitEvents=" << numWaitEvents
                << ", Delta: VmRSS=" << delta.vmRSS << "KB, VmSize=" << delta.vmSize << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendMemoryRangesBarrier", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendMemoryRangesBarrier: Ranges=" << numRanges
                << ", Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendMemoryCopy", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendMemoryCopy: Size=" << size << " bytes (" << (size / 1024) << " KB)"
                << ", Delta: VmRSS=" << delta.vmRSS << "KB, VmData=" << delta.vmData << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendMemoryFill", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendMemoryFill: Size=" << size << " bytes, PatternSize=" << pattern_size
                << ", Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendMemoryCopyRegion", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendMemoryCopyRegion: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendMemoryCopyFromContext", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendMemoryCopyFromContext: Size=" << size << " bytes"
                << ", Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendImageCopy", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendImageCopy: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendImageCopyRegion", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendImageCopyRegion: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendImageCopyToMemory", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendImageCopyToMemory: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendImageCopyFromMemory", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendImageCopyFromMemory: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemoryPrefetchEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          const void* ptr,
                                                                          size_t size,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendMemoryPrefetch", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendMemoryPrefetch: Size=" << size << " bytes"
                << ", Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendMemAdviseEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_device_handle_t hDevice,
                                                                          const void* ptr,
                                                                          size_t size,
                                                                          ze_memory_advice_t advice,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendMemAdvise", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendMemAdvise: Size=" << size << " bytes, Advice=" << advice
                << ", Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendSignalEventEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_event_handle_t hEvent,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendSignalEvent", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendSignalEvent: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendWaitOnEventsEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          uint32_t numEvents,
                                                                          ze_event_handle_t* phEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendWaitOnEvents", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendWaitOnEvents: NumEvents=" << numEvents
                << ", Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendEventResetEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          ze_event_handle_t hEvent,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendEventReset", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendEventReset: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendQueryKernelTimestamps", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendQueryKernelTimestamps: NumEvents=" << numEvents
                << ", Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendLaunchKernel", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendLaunchKernel";
            if (pLaunchFuncArgs) {
                msg << ": GroupCount=[" << pLaunchFuncArgs->groupCountX << "," 
                    << pLaunchFuncArgs->groupCountY << "," << pLaunchFuncArgs->groupCountZ << "]";
            }
            msg << ", Delta: VmRSS=" << delta.vmRSS << "KB, VmData=" << delta.vmData << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendLaunchCooperativeKernel", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendLaunchCooperativeKernel: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
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
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendLaunchKernelIndirect", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendLaunchKernelIndirect: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
    }

    ze_result_t system_resource_trackerChecker::ZEsystem_resource_trackerChecker::zeCommandListAppendWriteGlobalTimestampEpilogue(
                                                                          ze_command_list_handle_t hCommandList,
                                                                          uint64_t* dstptr,
                                                                          ze_event_handle_t hSignalEvent,
                                                                          uint32_t numWaitEvents,
                                                                          ze_event_handle_t* phWaitEvents,
                                                                          ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            std::lock_guard<std::mutex> lock(resourceTracker.trackerMutex);
            SystemResourceMetrics current = getSystemResourceMetrics();
            SystemResourceMetrics prevTotal = resourceTracker.commandLists;
            
            resourceTracker.commandLists = current - resourceTracker.baseline;
            SystemResourceMetrics delta = resourceTracker.commandLists - prevTotal;
            
            writeCsvData("zeCommandListAppendWriteGlobalTimestamp", current, delta);
            
            std::ostringstream msg;
            msg << "zeCommandListAppendWriteGlobalTimestamp: Delta: VmRSS=" << delta.vmRSS << "KB";
            context.logger->log_debug(msg.str());
        }
        return result;
    }
}