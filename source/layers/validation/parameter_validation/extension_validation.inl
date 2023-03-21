/*
 *
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file extension_validation.inl
 *
 */

inline ze_result_t validateStructureTypes(void *descriptorPtr,
                                   std::vector<ze_structure_type_t> &baseTypesVector,
                                   std::vector<ze_structure_type_t> &extensionTypesVector) {

    const ze_base_properties_t *pBase =
                            reinterpret_cast<const ze_base_properties_t*> (descriptorPtr);

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

     pBase = reinterpret_cast<const ze_base_properties_t*>(pBase->pNext);

    if ((extensionTypesVector).size()) {
        while(pBase) {
            bool validExtensionTypeFound = false;
            for (auto t : (extensionTypesVector)) {
                if (pBase->stype == t) {
                    validExtensionTypeFound = true;
                    break;
                }
            }
            if (!validExtensionTypeFound) {
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;
            }
            pBase = reinterpret_cast<const ze_base_properties_t*>(pBase->pNext);
        }
     }

     if (pBase) {
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
     }

     return ZE_RESULT_SUCCESS;
}

/* Begin device_imp.cpp cases */

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_p2p_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_P2P_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_DEVICE_P2P_BANDWIDTH_EXP_PROPERTIES};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_pci_ext_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_PCI_EXT_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_memory_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_MEMORY_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_DEVICE_MEMORY_EXT_PROPERTIES};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_memory_access_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_MEMORY_ACCESS_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_kernel_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_KERNEL_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_FLOAT_ATOMIC_EXT_PROPERTIES,
                                              ZE_STRUCTURE_TYPE_SCHEDULING_HINT_EXP_PROPERTIES,
                                              ZE_STRUCTURE_TYPE_DEVICE_RAYTRACING_EXT_PROPERTIES,
					      ZE_STRUCTURE_TYPE_KERNEL_PREFERRED_GROUP_SIZE_PROPERTIES};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES,
                                                  ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES_1_2};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_DEVICE_LUID_EXT_PROPERTIES,
                                              ZE_STRUCTURE_TYPE_EU_COUNT_EXT,
                                              ZE_STRUCTURE_TYPE_DEVICE_IP_VERSION_EXT};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_cache_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_CACHE_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_CACHE_RESERVATION_EXT_DESC};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_image_properties_t *descriptor) {
    
    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_IMAGE_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_compute_properties_t *descriptor) {
    
    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_module_properties_t *descriptor) {
    
    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_MODULE_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_command_queue_group_properties_t *descriptor) {
    
    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES,
                                              ZE_STRUCTURE_TYPE_COPY_BANDWIDTH_EXP_PROPERTIES};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_device_external_memory_properties_t *descriptor) {
    
    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DEVICE_EXTERNAL_MEMORY_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

/* END device_imp.cpp cases */

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_driver_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_DRIVER_MEMORY_FREE_EXT_PROPERTIES};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_driver_ipc_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_DRIVER_IPC_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_image_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_IMAGE_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_memory_allocation_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_MEMORY_ALLOCATION_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_FD,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_WIN32,
					      ZE_STRUCTURE_TYPE_MEMORY_SUB_ALLOCATIONS_EXP_PROPERTIES};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_image_allocation_ext_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_IMAGE_ALLOCATION_EXT_PROPERTIES};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_FD,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_WIN32};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_module_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_MODULE_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_fabric_vertex_exp_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_FABRIC_VERTEX_EXP_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_fabric_edge_exp_properties_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_FABRIC_EDGE_EXP_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_context_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_POWER_SAVING_HINT_EXP_DESC};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_command_queue_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_command_list_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC};
//    std::vector<ze_structure_type_t> types = {ZEX_STRUCTURE_TYPE_MUTABLE_COMMAND_LIST_DESCRIPTOR};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_event_pool_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_EVENT_POOL_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_event_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_EVENT_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_fence_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_FENCE_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_image_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_IMAGE_DESC};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_WIN32,
					      ZE_STRUCTURE_TYPE_MEMORY_COMPRESSION_HINTS_EXT_DESC};

    return validateStructureTypes(descriptor, baseTypes, types);
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

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_host_mem_alloc_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_RELAXED_ALLOCATION_LIMITS_EXP_DESC,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_DESC,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD,
					      ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_WIN32,
					      ZE_STRUCTURE_TYPE_MEMORY_COMPRESSION_HINTS_EXT_DESC};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_module_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_MODULE_DESC};
    std::vector<ze_structure_type_t> types = {ZE_STRUCTURE_TYPE_MODULE_PROGRAM_EXP_DESC};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_kernel_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_KERNEL_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_sampler_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_SAMPLER_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_physical_mem_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_PHYSICAL_MEM_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_scheduling_hint_exp_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_SCHEDULING_HINT_EXP_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

// couldn't find implementation
template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_linkage_inspection_ext_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_LINKAGE_INSPECTION_EXT_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_memory_free_ext_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_MEMORY_FREE_EXT_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}

template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_image_memory_properties_exp_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_IMAGE_MEMORY_EXP_PROPERTIES};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
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

    return validateStructureTypes(descriptor, baseTypes, types);
}

// THIS ONE IS PROBABLY NOT A VALID TEST
template <>
inline ze_result_t ParameterValidation::validateExtensions(ze_image_view_planar_exp_desc_t *descriptor) {

    std::vector<ze_structure_type_t> baseTypes = {ZE_STRUCTURE_TYPE_IMAGE_VIEW_PLANAR_EXP_DESC};
    std::vector<ze_structure_type_t> types = {};

    return validateStructureTypes(descriptor, baseTypes, types);
}
