/*
 *
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file extension_validation.inl
 *
 */
#include <type_traits>

template <typename S, typename B>
inline ze_result_t validateStructureTypes(const void *descriptorPtr,
                                   std::vector<S> &baseTypesVector,
                                   std::vector<S> &extensionTypesVector) {

    const B *pBase = reinterpret_cast<const B*> (descriptorPtr);

    if (pBase == nullptr) {
         return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }

     bool validBaseTypeFound = false;
     for (auto t : (baseTypesVector)) {
         if (pBase->stype == t) {
              validBaseTypeFound = true;
              break;
         }
     }
     if (!validBaseTypeFound) {
         return ZE_RESULT_ERROR_INVALID_ARGUMENT;
     }

     pBase = reinterpret_cast<const B*>(pBase->pNext);

    if ((extensionTypesVector).size()) {
        while(pBase) {
            bool validExtensionTypeFound = false;
            for (auto t : (extensionTypesVector)) {
                if (pBase->stype == t) {
                    validExtensionTypeFound = true;

                    // if extension type is ZE_STRUCTURE_TYPE_MODULE_PROGRAM_EXP_DESC
                    // then base type->format must be ZE_MODULE_FORMAT_IL_SPIRV
                    if (std::is_same<S, ze_structure_type_t>::value && (ZE_STRUCTURE_TYPE_MODULE_PROGRAM_EXP_DESC == static_cast<ze_structure_type_t>(t))){
                        if (ZE_MODULE_FORMAT_IL_SPIRV != reinterpret_cast<const ze_module_desc_t *>(descriptorPtr)->format){
                            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
                        }
                    }
                    break;
                }
            }
            if (!validExtensionTypeFound) {
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;
            }
            pBase = reinterpret_cast<const B*>(pBase->pNext);
        }
     }

     if (pBase) {
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
     }

     return ZE_RESULT_SUCCESS;
}

/* Begin ze_api cases */

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_p2p_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_P2P_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_DEVICE_P2P_BANDWIDTH_EXP_PROPERTIES};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t> (descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_pci_ext_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_PCI_EXT_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_memory_properties_t *descriptor) {

     if (descriptor == nullptr) {
       return ZE_RESULT_SUCCESS;
     }

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_MEMORY_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_DEVICE_MEMORY_EXT_PROPERTIES};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_memory_access_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_MEMORY_ACCESS_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_kernel_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_KERNEL_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_FLOAT_ATOMIC_EXT_PROPERTIES,
                                              ZE_STRUCTURE_TYPE_SCHEDULING_HINT_EXP_PROPERTIES,
                                              ZE_STRUCTURE_TYPE_DEVICE_RAYTRACING_EXT_PROPERTIES,
					      ZE_STRUCTURE_TYPE_KERNEL_PREFERRED_GROUP_SIZE_PROPERTIES};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES,
                                                  ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES_1_2};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_DEVICE_LUID_EXT_PROPERTIES,
                                              ZE_STRUCTURE_TYPE_EU_COUNT_EXT,
                                              ZE_STRUCTURE_TYPE_DEVICE_IP_VERSION_EXT};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_cache_properties_t *descriptor) {

    if (descriptor == nullptr) {
        return ZE_RESULT_SUCCESS;
    }

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_CACHE_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_CACHE_RESERVATION_EXT_DESC};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_image_properties_t *descriptor) {
    
    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_IMAGE_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_compute_properties_t *descriptor) {
    
    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_module_properties_t *descriptor) {
    
    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_MODULE_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_command_queue_group_properties_t *descriptor) {

     if (descriptor == nullptr) {
       return ZE_RESULT_SUCCESS;
     }

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES,
                                              ZE_STRUCTURE_TYPE_COPY_BANDWIDTH_EXP_PROPERTIES};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_external_memory_properties_t *descriptor) {
    
    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_EXTERNAL_MEMORY_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_driver_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_DRIVER_MEMORY_FREE_EXT_PROPERTIES};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_driver_ipc_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DRIVER_IPC_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_image_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_IMAGE_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_memory_allocation_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_MEMORY_ALLOCATION_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_FD,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_WIN32,
					      ZE_STRUCTURE_TYPE_MEMORY_SUB_ALLOCATIONS_EXP_PROPERTIES};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_image_allocation_ext_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_IMAGE_ALLOCATION_EXT_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_FD,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_WIN32};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_module_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_MODULE_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_fabric_vertex_exp_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_FABRIC_VERTEX_EXP_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_fabric_edge_exp_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_FABRIC_EDGE_EXP_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_context_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_POWER_SAVING_HINT_EXP_DESC};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_command_queue_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_command_list_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC};
//    std::vector<ze_structure_type_t> types = {ZEX_STRUCTURE_TYPE_MUTABLE_COMMAND_LIST_DESCRIPTOR};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_event_pool_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_EVENT_POOL_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_event_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_EVENT_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_fence_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_FENCE_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_image_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_IMAGE_DESC};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_WIN32,
					      ZE_STRUCTURE_TYPE_MEMORY_COMPRESSION_HINTS_EXT_DESC};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_mem_alloc_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_RELAXED_ALLOCATION_LIMITS_EXP_DESC,
					      ZE_STRUCTURE_TYPE_RAYTRACING_MEM_ALLOC_EXT_DESC,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_DESC,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_WIN32,
					      ZE_STRUCTURE_TYPE_MEMORY_COMPRESSION_HINTS_EXT_DESC};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_host_mem_alloc_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_RELAXED_ALLOCATION_LIMITS_EXP_DESC,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_DESC,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_WIN32,
					      ZE_STRUCTURE_TYPE_MEMORY_COMPRESSION_HINTS_EXT_DESC};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(const ze_module_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_MODULE_DESC};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_MODULE_PROGRAM_EXP_DESC};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_kernel_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_KERNEL_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_sampler_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_SAMPLER_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_physical_mem_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_PHYSICAL_MEM_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_scheduling_hint_exp_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_SCHEDULING_HINT_EXP_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

// couldn't find implementation
template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_linkage_inspection_ext_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_LINKAGE_INSPECTION_EXT_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_memory_free_ext_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_MEMORY_FREE_EXT_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_image_memory_properties_exp_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_IMAGE_MEMORY_EXP_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

// ze_driver_extension_properties_t is an [out] only structure, without stype, pNext
template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_driver_extension_properties_t  *descriptor) {

    return ZE_RESULT_SUCCESS;
}

// THIS ONE IS PROBABLY NOT A VALID TEST
template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_image_view_planar_ext_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_IMAGE_VIEW_PLANAR_EXT_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

// THIS ONE IS PROBABLY NOT A VALID TEST
template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_image_view_planar_exp_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_IMAGE_VIEW_PLANAR_EXP_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes<ze_structure_type_t, ze_base_properties_t>(descriptor, baseTypes, types);
}

/* Begin zet_api entries */

template <>
inline ze_result_t ParameterValidation::validateExtensions(zet_metric_group_properties_t *descriptor) {

    std::vector<zet_structure_type_t> baseTypes = {ZET_STRUCTURE_TYPE_METRIC_GROUP_PROPERTIES};
    std::vector<zet_structure_type_t> types = {ZET_STRUCTURE_TYPE_GLOBAL_METRICS_TIMESTAMPS_EXP_PROPERTIES};

    return validateStructureTypes<zet_structure_type_t, zet_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zet_metric_properties_t *descriptor) {

    std::vector<zet_structure_type_t> baseTypes = {ZET_STRUCTURE_TYPE_METRIC_PROPERTIES};
    std::vector<zet_structure_type_t> types = {};

    return validateStructureTypes<zet_structure_type_t, zet_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zet_metric_streamer_desc_t *descriptor) {

    std::vector<zet_structure_type_t> baseTypes = {ZET_STRUCTURE_TYPE_METRIC_STREAMER_DESC};
    std::vector<zet_structure_type_t> types = {};

    return validateStructureTypes<zet_structure_type_t, zet_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zet_metric_query_pool_desc_t *descriptor) {

    std::vector<zet_structure_type_t> baseTypes = {ZET_STRUCTURE_TYPE_METRIC_QUERY_POOL_DESC};
    std::vector<zet_structure_type_t> types = {};

    return validateStructureTypes<zet_structure_type_t, zet_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zet_profile_properties_t *descriptor) {

    std::vector<zet_structure_type_t> baseTypes = {ZET_STRUCTURE_TYPE_PROFILE_PROPERTIES};
    std::vector<zet_structure_type_t> types = {};

    return validateStructureTypes<zet_structure_type_t, zet_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zet_device_debug_properties_t *descriptor) {

    std::vector<zet_structure_type_t> baseTypes = {ZET_STRUCTURE_TYPE_DEVICE_DEBUG_PROPERTIES};
    std::vector<zet_structure_type_t> types = {};

    return validateStructureTypes<zet_structure_type_t, zet_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zet_debug_memory_space_desc_t *descriptor) {

    std::vector<zet_structure_type_t> baseTypes = {ZET_STRUCTURE_TYPE_DEBUG_MEMORY_SPACE_DESC};
    std::vector<zet_structure_type_t> types = {};

    return validateStructureTypes<zet_structure_type_t, zet_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zet_debug_regset_properties_t *descriptor) {

     if (descriptor == nullptr) {
       return ZE_RESULT_SUCCESS;
     }

    std::vector<zet_structure_type_t> baseTypes = {ZET_STRUCTURE_TYPE_DEBUG_REGSET_PROPERTIES};
    std::vector<zet_structure_type_t> types = {};

    return validateStructureTypes<zet_structure_type_t, zet_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zet_tracer_exp_desc_t *descriptor) {

    std::vector<zet_structure_type_t> baseTypes = {ZET_STRUCTURE_TYPE_TRACER_EXP_DESC};
    std::vector<zet_structure_type_t> types = {};

    return validateStructureTypes<zet_structure_type_t, zet_base_properties_t>(descriptor, baseTypes, types);
}

/* Begin zes_api entries */

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_device_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_DEVICE_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_pci_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_PCI_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_pci_bar_properties_t *descriptor) {

     if (descriptor == nullptr) {
       return ZE_RESULT_SUCCESS;
     }

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_PCI_BAR_PROPERTIES};
    std::vector<zes_structure_type_t> types = {ZES_STRUCTURE_TYPE_PCI_BAR_PROPERTIES_1_2};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_diag_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_DIAG_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_engine_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_ENGINE_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_fabric_port_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_FABRIC_PORT_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_fan_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_FAN_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_firmware_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_FIRMWARE_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_freq_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_FREQ_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_led_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_LED_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_mem_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_MEM_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_perf_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_PERF_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_power_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_POWER_PROPERTIES};
    std::vector<zes_structure_type_t> types = {ZES_STRUCTURE_TYPE_POWER_LIMIT_EXT_DESC,
                                               ZES_STRUCTURE_TYPE_POWER_EXT_PROPERTIES};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_psu_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_PSU_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_ras_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_RAS_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_sched_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_SCHED_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_sched_timeout_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_SCHED_TIMEOUT_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_sched_timeslice_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_SCHED_TIMESLICE_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_standby_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_STANDBY_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_temp_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_TEMP_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_device_state_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_DEVICE_STATE};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_process_state_t *descriptor) {

     if (descriptor == nullptr) {
       return ZE_RESULT_SUCCESS;
     }

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_PROCESS_STATE};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_pci_state_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_PCI_STATE};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_fabric_port_config_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_FABRIC_PORT_CONFIG};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_fabric_port_state_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_FABRIC_PORT_STATE};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_fan_config_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_FAN_CONFIG};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_freq_state_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_FREQ_STATE};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_oc_capabilities_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_OC_CAPABILITIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_led_state_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_LED_STATE};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_mem_state_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_MEM_STATE};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_psu_state_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_PSU_STATE};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

// This one is odd.  I don't find any actual uses of this one.
template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_base_state_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_BASE_STATE};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_ras_config_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_RAS_CONFIG};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_ras_state_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_RAS_STATE};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_temp_config_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_TEMP_CONFIG};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_device_ecc_desc_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_DEVICE_ECC_DESC};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_device_ecc_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_DEVICE_ECC_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_power_limit_ext_desc_t *descriptor) {

     if (descriptor == nullptr) {
       return ZE_RESULT_SUCCESS;
     }

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_POWER_LIMIT_EXT_DESC};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(zes_overclock_properties_t *descriptor) {

    std::vector<zes_structure_type_t> baseTypes = {ZES_STRUCTURE_TYPE_OVERCLOCK_PROPERTIES};
    std::vector<zes_structure_type_t> types = {};

    return validateStructureTypes<zes_structure_type_t, zes_base_properties_t>(descriptor, baseTypes, types);
}
