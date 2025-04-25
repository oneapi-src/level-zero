/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_libddi.cpp
 *
 */
#include "ze_lib.h"
#ifndef DYNAMIC_LOAD_LOADER
#include "zet_ddi.h"
#endif

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////

#ifdef DYNAMIC_LOAD_LOADER
    __zedlllocal ze_result_t context_t::zetDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zet_pfnGetMetricDecoderExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricDecoderExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzetDdiTable.MetricDecoderExp );
            initialzetDdiTable.MetricDecoderExp.pfnCreateExp = reinterpret_cast<zet_pfnMetricDecoderCreateExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricDecoderCreateExp") );
            initialzetDdiTable.MetricDecoderExp.pfnDestroyExp = reinterpret_cast<zet_pfnMetricDecoderDestroyExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricDecoderDestroyExp") );
            initialzetDdiTable.MetricDecoderExp.pfnGetDecodableMetricsExp = reinterpret_cast<zet_pfnMetricDecoderGetDecodableMetricsExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricDecoderGetDecodableMetricsExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zet_pfnGetMetricProgrammableExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricProgrammableExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzetDdiTable.MetricProgrammableExp );
            initialzetDdiTable.MetricProgrammableExp.pfnGetExp = reinterpret_cast<zet_pfnMetricProgrammableGetExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricProgrammableGetExp") );
            initialzetDdiTable.MetricProgrammableExp.pfnGetPropertiesExp = reinterpret_cast<zet_pfnMetricProgrammableGetPropertiesExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricProgrammableGetPropertiesExp") );
            initialzetDdiTable.MetricProgrammableExp.pfnGetParamInfoExp = reinterpret_cast<zet_pfnMetricProgrammableGetParamInfoExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricProgrammableGetParamInfoExp") );
            initialzetDdiTable.MetricProgrammableExp.pfnGetParamValueInfoExp = reinterpret_cast<zet_pfnMetricProgrammableGetParamValueInfoExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricProgrammableGetParamValueInfoExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zet_pfnGetMetricTracerExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricTracerExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzetDdiTable.MetricTracerExp );
            initialzetDdiTable.MetricTracerExp.pfnCreateExp = reinterpret_cast<zet_pfnMetricTracerCreateExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricTracerCreateExp") );
            initialzetDdiTable.MetricTracerExp.pfnDestroyExp = reinterpret_cast<zet_pfnMetricTracerDestroyExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricTracerDestroyExp") );
            initialzetDdiTable.MetricTracerExp.pfnEnableExp = reinterpret_cast<zet_pfnMetricTracerEnableExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricTracerEnableExp") );
            initialzetDdiTable.MetricTracerExp.pfnDisableExp = reinterpret_cast<zet_pfnMetricTracerDisableExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricTracerDisableExp") );
            initialzetDdiTable.MetricTracerExp.pfnReadDataExp = reinterpret_cast<zet_pfnMetricTracerReadDataExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricTracerReadDataExp") );
            initialzetDdiTable.MetricTracerExp.pfnDecodeExp = reinterpret_cast<zet_pfnMetricTracerDecodeExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricTracerDecodeExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDeviceProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.Device );
            initialzetDdiTable.Device.pfnGetDebugProperties = reinterpret_cast<zet_pfnDeviceGetDebugProperties_t>(
                GET_FUNCTION_PTR(loader, "zetDeviceGetDebugProperties") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zet_pfnGetDeviceExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDeviceExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzetDdiTable.DeviceExp );
            initialzetDdiTable.DeviceExp.pfnGetConcurrentMetricGroupsExp = reinterpret_cast<zet_pfnDeviceGetConcurrentMetricGroupsExp_t>(
                GET_FUNCTION_PTR(loader, "zetDeviceGetConcurrentMetricGroupsExp") );
            initialzetDdiTable.DeviceExp.pfnCreateMetricGroupsFromMetricsExp = reinterpret_cast<zet_pfnDeviceCreateMetricGroupsFromMetricsExp_t>(
                GET_FUNCTION_PTR(loader, "zetDeviceCreateMetricGroupsFromMetricsExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetContextProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetContextProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.Context );
            initialzetDdiTable.Context.pfnActivateMetricGroups = reinterpret_cast<zet_pfnContextActivateMetricGroups_t>(
                GET_FUNCTION_PTR(loader, "zetContextActivateMetricGroups") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetCommandListProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.CommandList );
            initialzetDdiTable.CommandList.pfnAppendMetricStreamerMarker = reinterpret_cast<zet_pfnCommandListAppendMetricStreamerMarker_t>(
                GET_FUNCTION_PTR(loader, "zetCommandListAppendMetricStreamerMarker") );
            initialzetDdiTable.CommandList.pfnAppendMetricQueryBegin = reinterpret_cast<zet_pfnCommandListAppendMetricQueryBegin_t>(
                GET_FUNCTION_PTR(loader, "zetCommandListAppendMetricQueryBegin") );
            initialzetDdiTable.CommandList.pfnAppendMetricQueryEnd = reinterpret_cast<zet_pfnCommandListAppendMetricQueryEnd_t>(
                GET_FUNCTION_PTR(loader, "zetCommandListAppendMetricQueryEnd") );
            initialzetDdiTable.CommandList.pfnAppendMetricMemoryBarrier = reinterpret_cast<zet_pfnCommandListAppendMetricMemoryBarrier_t>(
                GET_FUNCTION_PTR(loader, "zetCommandListAppendMetricMemoryBarrier") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetKernelProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.Kernel );
            initialzetDdiTable.Kernel.pfnGetProfileInfo = reinterpret_cast<zet_pfnKernelGetProfileInfo_t>(
                GET_FUNCTION_PTR(loader, "zetKernelGetProfileInfo") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetModuleProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.Module );
            initialzetDdiTable.Module.pfnGetDebugInfo = reinterpret_cast<zet_pfnModuleGetDebugInfo_t>(
                GET_FUNCTION_PTR(loader, "zetModuleGetDebugInfo") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDebugProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDebugProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.Debug );
            initialzetDdiTable.Debug.pfnAttach = reinterpret_cast<zet_pfnDebugAttach_t>(
                GET_FUNCTION_PTR(loader, "zetDebugAttach") );
            initialzetDdiTable.Debug.pfnDetach = reinterpret_cast<zet_pfnDebugDetach_t>(
                GET_FUNCTION_PTR(loader, "zetDebugDetach") );
            initialzetDdiTable.Debug.pfnReadEvent = reinterpret_cast<zet_pfnDebugReadEvent_t>(
                GET_FUNCTION_PTR(loader, "zetDebugReadEvent") );
            initialzetDdiTable.Debug.pfnAcknowledgeEvent = reinterpret_cast<zet_pfnDebugAcknowledgeEvent_t>(
                GET_FUNCTION_PTR(loader, "zetDebugAcknowledgeEvent") );
            initialzetDdiTable.Debug.pfnInterrupt = reinterpret_cast<zet_pfnDebugInterrupt_t>(
                GET_FUNCTION_PTR(loader, "zetDebugInterrupt") );
            initialzetDdiTable.Debug.pfnResume = reinterpret_cast<zet_pfnDebugResume_t>(
                GET_FUNCTION_PTR(loader, "zetDebugResume") );
            initialzetDdiTable.Debug.pfnReadMemory = reinterpret_cast<zet_pfnDebugReadMemory_t>(
                GET_FUNCTION_PTR(loader, "zetDebugReadMemory") );
            initialzetDdiTable.Debug.pfnWriteMemory = reinterpret_cast<zet_pfnDebugWriteMemory_t>(
                GET_FUNCTION_PTR(loader, "zetDebugWriteMemory") );
            initialzetDdiTable.Debug.pfnGetRegisterSetProperties = reinterpret_cast<zet_pfnDebugGetRegisterSetProperties_t>(
                GET_FUNCTION_PTR(loader, "zetDebugGetRegisterSetProperties") );
            initialzetDdiTable.Debug.pfnReadRegisters = reinterpret_cast<zet_pfnDebugReadRegisters_t>(
                GET_FUNCTION_PTR(loader, "zetDebugReadRegisters") );
            initialzetDdiTable.Debug.pfnWriteRegisters = reinterpret_cast<zet_pfnDebugWriteRegisters_t>(
                GET_FUNCTION_PTR(loader, "zetDebugWriteRegisters") );
            initialzetDdiTable.Debug.pfnGetThreadRegisterSetProperties = reinterpret_cast<zet_pfnDebugGetThreadRegisterSetProperties_t>(
                GET_FUNCTION_PTR(loader, "zetDebugGetThreadRegisterSetProperties") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.Metric );
            initialzetDdiTable.Metric.pfnGet = reinterpret_cast<zet_pfnMetricGet_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGet") );
            initialzetDdiTable.Metric.pfnGetProperties = reinterpret_cast<zet_pfnMetricGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGetProperties") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zet_pfnGetMetricExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzetDdiTable.MetricExp );
            initialzetDdiTable.MetricExp.pfnCreateFromProgrammableExp2 = reinterpret_cast<zet_pfnMetricCreateFromProgrammableExp2_t>(
                GET_FUNCTION_PTR(loader, "zetMetricCreateFromProgrammableExp2") );
            initialzetDdiTable.MetricExp.pfnCreateFromProgrammableExp = reinterpret_cast<zet_pfnMetricCreateFromProgrammableExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricCreateFromProgrammableExp") );
            initialzetDdiTable.MetricExp.pfnDestroyExp = reinterpret_cast<zet_pfnMetricDestroyExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricDestroyExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricGroupProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricGroupProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.MetricGroup );
            initialzetDdiTable.MetricGroup.pfnGet = reinterpret_cast<zet_pfnMetricGroupGet_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGroupGet") );
            initialzetDdiTable.MetricGroup.pfnGetProperties = reinterpret_cast<zet_pfnMetricGroupGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGroupGetProperties") );
            initialzetDdiTable.MetricGroup.pfnCalculateMetricValues = reinterpret_cast<zet_pfnMetricGroupCalculateMetricValues_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGroupCalculateMetricValues") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zet_pfnGetMetricGroupExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricGroupExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzetDdiTable.MetricGroupExp );
            initialzetDdiTable.MetricGroupExp.pfnCalculateMultipleMetricValuesExp = reinterpret_cast<zet_pfnMetricGroupCalculateMultipleMetricValuesExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGroupCalculateMultipleMetricValuesExp") );
            initialzetDdiTable.MetricGroupExp.pfnGetGlobalTimestampsExp = reinterpret_cast<zet_pfnMetricGroupGetGlobalTimestampsExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGroupGetGlobalTimestampsExp") );
            initialzetDdiTable.MetricGroupExp.pfnGetExportDataExp = reinterpret_cast<zet_pfnMetricGroupGetExportDataExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGroupGetExportDataExp") );
            initialzetDdiTable.MetricGroupExp.pfnCalculateMetricExportDataExp = reinterpret_cast<zet_pfnMetricGroupCalculateMetricExportDataExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGroupCalculateMetricExportDataExp") );
            initialzetDdiTable.MetricGroupExp.pfnCreateExp = reinterpret_cast<zet_pfnMetricGroupCreateExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGroupCreateExp") );
            initialzetDdiTable.MetricGroupExp.pfnAddMetricExp = reinterpret_cast<zet_pfnMetricGroupAddMetricExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGroupAddMetricExp") );
            initialzetDdiTable.MetricGroupExp.pfnRemoveMetricExp = reinterpret_cast<zet_pfnMetricGroupRemoveMetricExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGroupRemoveMetricExp") );
            initialzetDdiTable.MetricGroupExp.pfnCloseExp = reinterpret_cast<zet_pfnMetricGroupCloseExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGroupCloseExp") );
            initialzetDdiTable.MetricGroupExp.pfnDestroyExp = reinterpret_cast<zet_pfnMetricGroupDestroyExp_t>(
                GET_FUNCTION_PTR(loader, "zetMetricGroupDestroyExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricQueryProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.MetricQuery );
            initialzetDdiTable.MetricQuery.pfnCreate = reinterpret_cast<zet_pfnMetricQueryCreate_t>(
                GET_FUNCTION_PTR(loader, "zetMetricQueryCreate") );
            initialzetDdiTable.MetricQuery.pfnDestroy = reinterpret_cast<zet_pfnMetricQueryDestroy_t>(
                GET_FUNCTION_PTR(loader, "zetMetricQueryDestroy") );
            initialzetDdiTable.MetricQuery.pfnReset = reinterpret_cast<zet_pfnMetricQueryReset_t>(
                GET_FUNCTION_PTR(loader, "zetMetricQueryReset") );
            initialzetDdiTable.MetricQuery.pfnGetData = reinterpret_cast<zet_pfnMetricQueryGetData_t>(
                GET_FUNCTION_PTR(loader, "zetMetricQueryGetData") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricQueryPoolProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.MetricQueryPool );
            initialzetDdiTable.MetricQueryPool.pfnCreate = reinterpret_cast<zet_pfnMetricQueryPoolCreate_t>(
                GET_FUNCTION_PTR(loader, "zetMetricQueryPoolCreate") );
            initialzetDdiTable.MetricQueryPool.pfnDestroy = reinterpret_cast<zet_pfnMetricQueryPoolDestroy_t>(
                GET_FUNCTION_PTR(loader, "zetMetricQueryPoolDestroy") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricStreamerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricStreamerProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.MetricStreamer );
            initialzetDdiTable.MetricStreamer.pfnOpen = reinterpret_cast<zet_pfnMetricStreamerOpen_t>(
                GET_FUNCTION_PTR(loader, "zetMetricStreamerOpen") );
            initialzetDdiTable.MetricStreamer.pfnClose = reinterpret_cast<zet_pfnMetricStreamerClose_t>(
                GET_FUNCTION_PTR(loader, "zetMetricStreamerClose") );
            initialzetDdiTable.MetricStreamer.pfnReadData = reinterpret_cast<zet_pfnMetricStreamerReadData_t>(
                GET_FUNCTION_PTR(loader, "zetMetricStreamerReadData") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetTracerExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetTracerExpProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.TracerExp );
            initialzetDdiTable.TracerExp.pfnCreate = reinterpret_cast<zet_pfnTracerExpCreate_t>(
                GET_FUNCTION_PTR(loader, "zetTracerExpCreate") );
            initialzetDdiTable.TracerExp.pfnDestroy = reinterpret_cast<zet_pfnTracerExpDestroy_t>(
                GET_FUNCTION_PTR(loader, "zetTracerExpDestroy") );
            initialzetDdiTable.TracerExp.pfnSetPrologues = reinterpret_cast<zet_pfnTracerExpSetPrologues_t>(
                GET_FUNCTION_PTR(loader, "zetTracerExpSetPrologues") );
            initialzetDdiTable.TracerExp.pfnSetEpilogues = reinterpret_cast<zet_pfnTracerExpSetEpilogues_t>(
                GET_FUNCTION_PTR(loader, "zetTracerExpSetEpilogues") );
            initialzetDdiTable.TracerExp.pfnSetEnabled = reinterpret_cast<zet_pfnTracerExpSetEnabled_t>(
                GET_FUNCTION_PTR(loader, "zetTracerExpSetEnabled") );
        }

        return result;
    }
#else
    __zedlllocal ze_result_t context_t::zetDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zetGetMetricDecoderExpProcAddrTable( version, &initialzetDdiTable.MetricDecoderExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zetGetMetricProgrammableExpProcAddrTable( version, &initialzetDdiTable.MetricProgrammableExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zetGetMetricTracerExpProcAddrTable( version, &initialzetDdiTable.MetricTracerExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetDeviceProcAddrTable( version, &initialzetDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zetGetDeviceExpProcAddrTable( version, &initialzetDdiTable.DeviceExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetContextProcAddrTable( version, &initialzetDdiTable.Context );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetCommandListProcAddrTable( version, &initialzetDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetKernelProcAddrTable( version, &initialzetDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetModuleProcAddrTable( version, &initialzetDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetDebugProcAddrTable( version, &initialzetDdiTable.Debug );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricProcAddrTable( version, &initialzetDdiTable.Metric );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zetGetMetricExpProcAddrTable( version, &initialzetDdiTable.MetricExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricGroupProcAddrTable( version, &initialzetDdiTable.MetricGroup );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zetGetMetricGroupExpProcAddrTable( version, &initialzetDdiTable.MetricGroupExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricQueryProcAddrTable( version, &initialzetDdiTable.MetricQuery );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricQueryPoolProcAddrTable( version, &initialzetDdiTable.MetricQueryPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricStreamerProcAddrTable( version, &initialzetDdiTable.MetricStreamer );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetTracerExpProcAddrTable( version, &initialzetDdiTable.TracerExp );
        }

        return result;
    }
#endif

} // namespace ze_lib
