/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "ze_handle_lifetime.h"
#include "zes_handle_lifetime.h"
#include "zet_handle_lifetime.h"
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

namespace validation_layer {

typedef struct _zel_handle_state_t {
  bool is_open;
} zel_handle_state_t;

class HandleLifetimeValidation {
public:
  ZEHandleLifetimeValidation zeHandleLifetime;
  ZESHandleLifetimeValidation zesHandleLifetime;
  ZETHandleLifetimeValidation zetHandleLifetime;

  // default methods
  template <class T> void addHandle(T handle) {
    // TODO : Log warning
    untrackedHandles++;
    defaultHandleStateMap.insert({static_cast<void *>(handle), nullptr});
  }

  template <class T> void removeHandle(T handle) {
    // TODO: Log warning
    untrackedHandles--;
    defaultHandleStateMap.erase(static_cast<void *>(handle));
  }

  template <class T> bool isHandleValid(T handle) {
    return defaultHandleStateMap.find(static_cast<void *>(handle)) !=
           defaultHandleStateMap.end();
  }

  template <class S, class T> S get_handle_map(T handle) {
    if (std::is_same<T, ze_context_handle_t>::value) {
      return contextHandleStateMap;
    } else if (std::is_same<T, ze_driver_handle_t>::value) {
      return driverHandleStateMap;
    } else {
      return defaultHandleStateMap;
    }
  }

  void addHandle(ze_context_handle_t handle) {
    contextHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_driver_handle_t handle) {
    driverHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_device_handle_t handle) {
    deviceHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_command_queue_handle_t handle) {
    commandQueueHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_command_list_handle_t handle, bool is_open = true) {
    commandListHandleStateMap.insert(
        {handle, std::make_unique<zel_handle_state_t>()});
    commandListHandleStateMap[handle]->is_open = is_open;
  }
  void addHandle(ze_fence_handle_t handle) {
    fenceHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_event_pool_handle_t handle) {
    eventPoolHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_event_handle_t handle) {
    eventHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_image_handle_t handle) {
    imageHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_module_handle_t handle) {
    moduleHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_module_build_log_handle_t handle) {
    moduleBuildLogHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_kernel_handle_t handle) {
    kernelHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_sampler_handle_t handle) {
    samplerHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_fabric_vertex_handle_t handle) {
    fabricVertexHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_fabric_edge_handle_t handle) {
    fabricEdgeHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_physical_mem_handle_t handle) {
    physicalMemHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_ipc_event_pool_handle_t handle) {
    ipcEventPoolHandleStateMap.insert({&handle, nullptr});
  }
  void addHandle(ze_ipc_mem_handle_t handle) {
    ipcMemHandleStateMap.insert({&handle, nullptr});
  }
  void addHandle(ze_external_memory_import_win32_handle_t &handle) {
    externalMemoryImportWin32HandleStateMap.insert({&handle, nullptr});
  }
  void addHandle(ze_external_memory_export_win32_handle_t &handle) {
    externalMemoryExportWin32HandleStateMap.insert({&handle, nullptr});
  }

  void addHandle(zet_metric_group_handle_t handle) {
    metricGroupHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zet_metric_handle_t handle) {
    metricHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zet_metric_streamer_handle_t handle) {
    metricStreamerHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zet_metric_query_pool_handle_t handle) {
    metricQueryPoolHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zet_metric_query_handle_t handle) {
    metricQueryHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zet_tracer_exp_handle_t handle) {
    tracerExpHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zet_debug_session_handle_t handle) {
    debugSessionHandleStateMap.insert({handle, nullptr});
  }

  void addHandle(zes_sched_handle_t handle) {
    schedHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_perf_handle_t handle) {
    perfHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_pwr_handle_t handle) {
    pwrHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_freq_handle_t handle) {
    freqHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_engine_handle_t handle) {
    engineHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_standby_handle_t handle) {
    standbyHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_firmware_handle_t handle) {
    firmwareHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_mem_handle_t handle) {
    memHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_fabric_port_handle_t handle) {
    fabricPortHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_temp_handle_t handle) {
    tempHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_psu_handle_t handle) {
    psuHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_fan_handle_t handle) {
    fanHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_led_handle_t handle) {
    ledHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_ras_handle_t handle) {
    rasHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_diag_handle_t handle) {
    diagHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(zes_overclock_handle_t handle) {
    overclockHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_rtas_parallel_operation_exp_handle_t handle) {
    rtasParallelOperationHandleStateMap.insert({handle, nullptr});
  }
  void addHandle(ze_rtas_builder_exp_handle_t handle) {
    rtasBuilderHandleStateMap.insert({handle, nullptr});
  }

  void removeHandle(ze_context_handle_t handle) {
    contextHandleStateMap.erase(handle);
  }
  void removeHandle(ze_driver_handle_t handle) {
    driverHandleStateMap.erase(handle);
  }
  void removeHandle(ze_device_handle_t handle) {
    deviceHandleStateMap.erase(handle);
  }
  void removeHandle(ze_command_queue_handle_t handle) {
    commandQueueHandleStateMap.erase(handle);
  }
  void removeHandle(ze_command_list_handle_t handle) {
    commandListHandleStateMap.erase(handle);
  }
  void removeHandle(ze_fence_handle_t handle) {
    fenceHandleStateMap.erase(handle);
  }
  void removeHandle(ze_event_pool_handle_t handle) {
    eventPoolHandleStateMap.erase(handle);
  }
  void removeHandle(ze_event_handle_t handle) {
    eventHandleStateMap.erase(handle);
  }
  void removeHandle(ze_image_handle_t handle) {
    imageHandleStateMap.erase(handle);
  }
  void removeHandle(ze_module_handle_t handle) {
    moduleHandleStateMap.erase(handle);
  }
  void removeHandle(ze_module_build_log_handle_t handle) {
    moduleBuildLogHandleStateMap.erase(handle);
  }
  void removeHandle(ze_kernel_handle_t handle) {
    kernelHandleStateMap.erase(handle);
  }
  void removeHandle(ze_sampler_handle_t handle) {
    samplerHandleStateMap.erase(handle);
  }
  void removeHandle(ze_physical_mem_handle_t handle) {
    physicalMemHandleStateMap.erase(handle);
  }
  void removeHandle(ze_fabric_vertex_handle_t handle) {
    fabricVertexHandleStateMap.erase(handle);
  }
  void removeHandle(ze_fabric_edge_handle_t handle) {
    fabricEdgeHandleStateMap.erase(handle);
  }
  void removeHandle(ze_ipc_mem_handle_t &handle) {
    ipcMemHandleStateMap.erase(&handle);
  }
  void removeHandle(ze_ipc_event_pool_handle_t &handle) {
    ipcEventPoolHandleStateMap.erase(&handle);
  }
  void removeHandle(ze_external_memory_export_win32_handle_t &handle) {
    externalMemoryExportWin32HandleStateMap.erase(&handle);
  }
  void removeHandle(ze_external_memory_import_win32_handle_t &handle) {
    externalMemoryImportWin32HandleStateMap.erase(&handle);
  }

  void removeHandle(zet_metric_group_handle_t handle) {
    metricGroupHandleStateMap.erase(handle);
  }
  void removeHandle(zet_metric_handle_t handle) {
    metricHandleStateMap.erase(handle);
  }
  void removeHandle(zet_metric_streamer_handle_t handle) {
    metricStreamerHandleStateMap.erase(handle);
  }
  void removeHandle(zet_metric_query_pool_handle_t handle) {
    metricQueryPoolHandleStateMap.erase(handle);
  }
  void removeHandle(zet_metric_query_handle_t handle) {
    metricQueryHandleStateMap.erase(handle);
  }
  void removeHandle(zet_tracer_exp_handle_t handle) {
    tracerExpHandleStateMap.erase(handle);
  }
  void removeHandle(zet_debug_session_handle_t handle) {
    debugSessionHandleStateMap.erase(handle);
  }

  void removeHandle(zes_sched_handle_t handle) {
    schedHandleStateMap.erase(handle);
  }
  void removeHandle(zes_perf_handle_t handle) {
    perfHandleStateMap.erase(handle);
  }
  void removeHandle(zes_pwr_handle_t handle) {
    pwrHandleStateMap.erase(handle);
  }
  void removeHandle(zes_freq_handle_t handle) {
    freqHandleStateMap.erase(handle);
  }
  void removeHandle(zes_engine_handle_t handle) {
    engineHandleStateMap.erase(handle);
  }
  void removeHandle(zes_standby_handle_t handle) {
    standbyHandleStateMap.erase(handle);
  }
  void removeHandle(zes_firmware_handle_t handle) {
    firmwareHandleStateMap.erase(handle);
  }
  void removeHandle(zes_mem_handle_t handle) {
    memHandleStateMap.erase(handle);
  }
  void removeHandle(zes_fabric_port_handle_t handle) {
    fabricPortHandleStateMap.erase(handle);
  }
  void removeHandle(zes_temp_handle_t handle) {
    tempHandleStateMap.erase(handle);
  }
  void removeHandle(zes_psu_handle_t handle) {
    psuHandleStateMap.erase(handle);
  }
  void removeHandle(zes_fan_handle_t handle) {
    fanHandleStateMap.erase(handle);
  }
  void removeHandle(zes_led_handle_t handle) {
    ledHandleStateMap.erase(handle);
  }
  void removeHandle(zes_ras_handle_t handle) {
    rasHandleStateMap.erase(handle);
  }
  void removeHandle(zes_diag_handle_t handle) {
    diagHandleStateMap.erase(handle);
  }
  void removeHandle(zes_overclock_handle_t handle) {
    overclockHandleStateMap.erase(handle);
  }
  void removeHandle(ze_rtas_parallel_operation_exp_handle_t handle) {
    rtasParallelOperationHandleStateMap.erase(handle);
  }
  void removeHandle(ze_rtas_builder_exp_handle_t handle) {
    rtasBuilderHandleStateMap.erase(handle);
  }

  bool isHandleValid(ze_context_handle_t handle) {
    return contextHandleStateMap.find(handle) != contextHandleStateMap.end();
  }
  bool isHandleValid(ze_driver_handle_t handle) {
    return driverHandleStateMap.find(handle) != driverHandleStateMap.end();
  }
  bool isHandleValid(ze_device_handle_t handle) {
    return deviceHandleStateMap.find(handle) != deviceHandleStateMap.end();
  }
  bool isHandleValid(ze_command_queue_handle_t handle) {
    return commandQueueHandleStateMap.find(handle) !=
           commandQueueHandleStateMap.end();
  }
  bool isHandleValid(ze_command_list_handle_t handle) {
    return commandListHandleStateMap.find(handle) !=
           commandListHandleStateMap.end();
  }
  bool isHandleValid(ze_fence_handle_t handle) {
    return fenceHandleStateMap.find(handle) != fenceHandleStateMap.end();
  }
  bool isHandleValid(ze_event_pool_handle_t handle) {
    return eventPoolHandleStateMap.find(handle) !=
           eventPoolHandleStateMap.end();
  }
  bool isHandleValid(ze_event_handle_t handle) {
    return eventHandleStateMap.find(handle) != eventHandleStateMap.end();
  }
  bool isHandleValid(ze_image_handle_t handle) {
    return imageHandleStateMap.find(handle) != imageHandleStateMap.end();
  }
  bool isHandleValid(ze_module_handle_t handle) {
    return moduleHandleStateMap.find(handle) != moduleHandleStateMap.end();
  }
  bool isHandleValid(ze_module_build_log_handle_t handle) {
    return moduleBuildLogHandleStateMap.find(handle) !=
           moduleBuildLogHandleStateMap.end();
  }
  bool isHandleValid(ze_kernel_handle_t handle) {
    return kernelHandleStateMap.find(handle) != kernelHandleStateMap.end();
  }
  bool isHandleValid(ze_sampler_handle_t handle) {
    return samplerHandleStateMap.find(handle) != samplerHandleStateMap.end();
  }
  bool isHandleValid(ze_physical_mem_handle_t handle) {
    return physicalMemHandleStateMap.find(handle) !=
           physicalMemHandleStateMap.end();
  }
  bool isHandleValid(ze_fabric_vertex_handle_t handle) {
    return fabricVertexHandleStateMap.find(handle) !=
           fabricVertexHandleStateMap.end();
  }
  bool isHandleValid(ze_fabric_edge_handle_t handle) {
    return fabricEdgeHandleStateMap.find(handle) !=
           fabricEdgeHandleStateMap.end();
  }
  bool isHandleValid(ze_ipc_mem_handle_t &handle) {
    return ipcMemHandleStateMap.find(&handle) != ipcMemHandleStateMap.end();
  }
  bool isHandleValid(ze_ipc_event_pool_handle_t &handle) {
    return ipcEventPoolHandleStateMap.find(&handle) !=
           ipcEventPoolHandleStateMap.end();
  }
  bool isHandleValid(ze_external_memory_import_win32_handle_t &handle) {
    return externalMemoryImportWin32HandleStateMap.find(&handle) !=
           externalMemoryImportWin32HandleStateMap.end();
  }
  bool isHandleValid(ze_external_memory_export_win32_handle_t &handle) {
    return externalMemoryExportWin32HandleStateMap.find(&handle) !=
           externalMemoryExportWin32HandleStateMap.end();
  }

  bool isHandleValid(zet_metric_group_handle_t handle) {
    return metricGroupHandleStateMap.find(handle) !=
           metricGroupHandleStateMap.end();
  }
  bool isHandleValid(zet_metric_handle_t handle) {
    return metricHandleStateMap.find(handle) != metricHandleStateMap.end();
  }
  bool isHandleValid(zet_metric_streamer_handle_t handle) {
    return metricStreamerHandleStateMap.find(handle) !=
           metricStreamerHandleStateMap.end();
  }
  bool isHandleValid(zet_metric_query_pool_handle_t handle) {
    return metricQueryPoolHandleStateMap.find(handle) !=
           metricQueryPoolHandleStateMap.end();
  }
  bool isHandleValid(zet_metric_query_handle_t handle) {
    return metricQueryHandleStateMap.find(handle) !=
           metricQueryHandleStateMap.end();
  }
  bool isHandleValid(zet_tracer_exp_handle_t handle) {
    return tracerExpHandleStateMap.find(handle) !=
           tracerExpHandleStateMap.end();
  }
  bool isHandleValid(zet_debug_session_handle_t handle) {
    return debugSessionHandleStateMap.find(handle) !=
           debugSessionHandleStateMap.end();
  }

  bool isHandleValid(zes_sched_handle_t handle) {
    return schedHandleStateMap.find(handle) != schedHandleStateMap.end();
  }
  bool isHandleValid(zes_perf_handle_t handle) {
    return perfHandleStateMap.find(handle) != perfHandleStateMap.end();
  }
  bool isHandleValid(zes_pwr_handle_t handle) {
    return pwrHandleStateMap.find(handle) != pwrHandleStateMap.end();
  }
  bool isHandleValid(zes_freq_handle_t handle) {
    return freqHandleStateMap.find(handle) != freqHandleStateMap.end();
  }
  bool isHandleValid(zes_engine_handle_t handle) {
    return engineHandleStateMap.find(handle) != engineHandleStateMap.end();
  }
  bool isHandleValid(zes_standby_handle_t handle) {
    return standbyHandleStateMap.find(handle) != standbyHandleStateMap.end();
  }
  bool isHandleValid(zes_firmware_handle_t handle) {
    return firmwareHandleStateMap.find(handle) != firmwareHandleStateMap.end();
  }
  bool isHandleValid(zes_mem_handle_t handle) {
    return memHandleStateMap.find(handle) != memHandleStateMap.end();
  }
  bool isHandleValid(zes_fabric_port_handle_t handle) {
    return fabricPortHandleStateMap.find(handle) !=
           fabricPortHandleStateMap.end();
  }
  bool isHandleValid(zes_temp_handle_t handle) {
    return tempHandleStateMap.find(handle) != tempHandleStateMap.end();
  }
  bool isHandleValid(zes_psu_handle_t handle) {
    return psuHandleStateMap.find(handle) != psuHandleStateMap.end();
  }
  bool isHandleValid(zes_fan_handle_t handle) {
    return fanHandleStateMap.find(handle) != fanHandleStateMap.end();
  }
  bool isHandleValid(zes_led_handle_t handle) {
    return ledHandleStateMap.find(handle) != ledHandleStateMap.end();
  }
  bool isHandleValid(zes_ras_handle_t handle) {
    return rasHandleStateMap.find(handle) != rasHandleStateMap.end();
  }
  bool isHandleValid(zes_diag_handle_t handle) {
    return diagHandleStateMap.find(handle) != diagHandleStateMap.end();
  }
  bool isHandleValid(zes_overclock_handle_t handle) {
    return overclockHandleStateMap.find(handle) !=
           overclockHandleStateMap.end();
  }

  bool isHandleValid(ze_rtas_parallel_operation_exp_handle_t handle) {
    return rtasParallelOperationHandleStateMap.find(handle) !=
           rtasParallelOperationHandleStateMap.end();
  }

  bool isHandleValid(ze_rtas_builder_exp_handle_t handle) {
    return rtasBuilderHandleStateMap.find(handle) !=
           rtasBuilderHandleStateMap.end();
  }

  bool isOpen(ze_command_list_handle_t handle) {
    return commandListHandleStateMap[handle]->is_open;
  }
  void close(ze_command_list_handle_t handle) {
    commandListHandleStateMap[handle]->is_open = false;
  }
  void reset(ze_command_list_handle_t handle) {
    commandListHandleStateMap[handle]->is_open = true;
  }

  void printDependentMap() {

    printf("\n--------------------------------------------\n");
    for (auto &handle : dependentMap) {
      printf("Handle: %p Dependents: {", handle.first);

      for (auto dependent : handle.second) {
        printf(" %p ", dependent);
      }
      printf("}\n");
    }
    printf("--------------------------------------------\n");
  }

  void addDependent(const void *handle, const void *dependent) {
    // No need to track driver dependents
    for (auto &driverHandle : driverHandleStateMap){
      if (handle == (void*)driverHandle.first){
        return;
      }
    }

    if (dependentMap.count(handle) == 0) {
      dependentMap[handle] = std::unordered_set<const void *>();
    }
    dependentMap[handle].insert(dependent);
  }

  void removeDependent(const void *dependent) {
    for (auto &handle : dependentMap) {
      handle.second.erase(dependent);
    }
  }

  void removeDependent(const void *handle, const void *dependent) {
    if (dependentMap.count(handle) == 0) {
      return;
    }
    dependentMap[handle].erase(dependent);
  }

  bool hasDependents(const void *handle) {
    return dependentMap.count(handle) && !dependentMap[handle].empty();
  }

private:
  std::unordered_map<void *, std::unique_ptr<zel_handle_state_t>>
      defaultHandleStateMap;
  std::unordered_map<ze_context_handle_t, std::unique_ptr<zel_handle_state_t>>
      contextHandleStateMap;
  std::unordered_map<ze_driver_handle_t, std::unique_ptr<zel_handle_state_t>>
      driverHandleStateMap;
  std::unordered_map<ze_device_handle_t, std::unique_ptr<zel_handle_state_t>>
      deviceHandleStateMap;
  std::unordered_map<ze_command_queue_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      commandQueueHandleStateMap;
  std::unordered_map<ze_command_list_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      commandListHandleStateMap;
  std::unordered_map<ze_fence_handle_t, std::unique_ptr<zel_handle_state_t>>
      fenceHandleStateMap;
  std::unordered_map<ze_event_pool_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      eventPoolHandleStateMap;
  std::unordered_map<ze_event_handle_t, std::unique_ptr<zel_handle_state_t>>
      eventHandleStateMap;
  std::unordered_map<ze_image_handle_t, std::unique_ptr<zel_handle_state_t>>
      imageHandleStateMap;
  std::unordered_map<ze_module_handle_t, std::unique_ptr<zel_handle_state_t>>
      moduleHandleStateMap;
  std::unordered_map<ze_module_build_log_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      moduleBuildLogHandleStateMap;
  std::unordered_map<ze_kernel_handle_t, std::unique_ptr<zel_handle_state_t>>
      kernelHandleStateMap;
  std::unordered_map<ze_sampler_handle_t, std::unique_ptr<zel_handle_state_t>>
      samplerHandleStateMap;
  std::unordered_map<ze_physical_mem_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      physicalMemHandleStateMap;

  std::unordered_map<ze_fabric_vertex_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      fabricVertexHandleStateMap;
  std::unordered_map<ze_fabric_edge_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      fabricEdgeHandleStateMap;

  std::unordered_map<ze_ipc_event_pool_handle_t *,
                     std::unique_ptr<zel_handle_state_t>>
      ipcEventPoolHandleStateMap;
  std::unordered_map<ze_ipc_mem_handle_t *, std::unique_ptr<zel_handle_state_t>>
      ipcMemHandleStateMap;

  std::unordered_map<ze_external_memory_import_win32_handle_t *,
                     std::unique_ptr<zel_handle_state_t>>
      externalMemoryImportWin32HandleStateMap;
  std::unordered_map<ze_external_memory_export_win32_handle_t *,
                     std::unique_ptr<zel_handle_state_t>>
      externalMemoryExportWin32HandleStateMap;

  // tools
  std::unordered_map<zet_driver_handle_t, std::unique_ptr<zel_handle_state_t>>
      zetDriverHandleStateMap;
  std::unordered_map<zet_device_handle_t, std::unique_ptr<zel_handle_state_t>>
      zetDeviceHandleStateMap;
  std::unordered_map<zet_context_handle_t, std::unique_ptr<zel_handle_state_t>>
      zetContextHandleStateMap;
  std::unordered_map<zet_command_list_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      zetCommandListHandleStateMap;
  std::unordered_map<zet_module_handle_t, std::unique_ptr<zel_handle_state_t>>
      zetModuleHandleStateMap;
  std::unordered_map<zet_kernel_handle_t, std::unique_ptr<zel_handle_state_t>>
      zetKernelHandleStateMap;
  std::unordered_map<zet_metric_group_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      metricGroupHandleStateMap;
  std::unordered_map<zet_metric_handle_t, std::unique_ptr<zel_handle_state_t>>
      metricHandleStateMap;
  std::unordered_map<zet_metric_streamer_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      metricStreamerHandleStateMap;
  std::unordered_map<zet_metric_query_pool_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      metricQueryPoolHandleStateMap;
  std::unordered_map<zet_metric_query_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      metricQueryHandleStateMap;
  std::unordered_map<zet_tracer_exp_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      tracerExpHandleStateMap;
  std::unordered_map<zet_debug_session_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      debugSessionHandleStateMap;

  // sysman
  std::unordered_map<zes_driver_handle_t, std::unique_ptr<zel_handle_state_t>>
      zesDriverHandleStateMap;
  std::unordered_map<zes_device_handle_t, std::unique_ptr<zel_handle_state_t>>
      zesDeviceHandleStateMap;
  std::unordered_map<zes_sched_handle_t, std::unique_ptr<zel_handle_state_t>>
      schedHandleStateMap;
  std::unordered_map<zes_perf_handle_t, std::unique_ptr<zel_handle_state_t>>
      perfHandleStateMap;
  std::unordered_map<zes_pwr_handle_t, std::unique_ptr<zel_handle_state_t>>
      pwrHandleStateMap;
  std::unordered_map<zes_freq_handle_t, std::unique_ptr<zel_handle_state_t>>
      freqHandleStateMap;
  std::unordered_map<zes_engine_handle_t, std::unique_ptr<zel_handle_state_t>>
      engineHandleStateMap;
  std::unordered_map<zes_standby_handle_t, std::unique_ptr<zel_handle_state_t>>
      standbyHandleStateMap;
  std::unordered_map<zes_firmware_handle_t, std::unique_ptr<zel_handle_state_t>>
      firmwareHandleStateMap;
  std::unordered_map<zes_mem_handle_t, std::unique_ptr<zel_handle_state_t>>
      memHandleStateMap;
  std::unordered_map<zes_fabric_port_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      fabricPortHandleStateMap;
  std::unordered_map<zes_temp_handle_t, std::unique_ptr<zel_handle_state_t>>
      tempHandleStateMap;
  std::unordered_map<zes_psu_handle_t, std::unique_ptr<zel_handle_state_t>>
      psuHandleStateMap;
  std::unordered_map<zes_fan_handle_t, std::unique_ptr<zel_handle_state_t>>
      fanHandleStateMap;
  std::unordered_map<zes_led_handle_t, std::unique_ptr<zel_handle_state_t>>
      ledHandleStateMap;
  std::unordered_map<zes_ras_handle_t, std::unique_ptr<zel_handle_state_t>>
      rasHandleStateMap;
  std::unordered_map<zes_diag_handle_t, std::unique_ptr<zel_handle_state_t>>
      diagHandleStateMap;
  std::unordered_map<zes_overclock_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      overclockHandleStateMap;
  std::unordered_map<ze_rtas_parallel_operation_exp_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      rtasParallelOperationHandleStateMap;
  std::unordered_map<ze_rtas_builder_exp_handle_t,
                     std::unique_ptr<zel_handle_state_t>>
      rtasBuilderHandleStateMap;

  std::unordered_map<const void *, std::unordered_set<const void *>>
      dependentMap;

  int untrackedHandles = 0;

}; // class HandleLifetimeValidation

} // namespace validation_layer
