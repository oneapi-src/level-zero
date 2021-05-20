/*
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_loader.h
 */

#ifndef _ZE_LOADER_H
#define _ZE_LOADER_H
#if defined(__cplusplus)
#pragma once
#endif

#include "ze_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

 typedef struct _zel_version {
    int major;
    int minor;
    int patch; 
  } zel_version_t; 

 //Ex component string "ze_tracing", "ze_validation", etc 
#define ZEL_COMPONENT_STRING_SIZE 64 

 typedef struct zel_component_version {
    char component_name[ZEL_COMPONENT_STRING_SIZE];
    ze_api_version_t spec_version;
    zel_version_t component_lib_version;
} zel_component_version_t; 


ZE_APIEXPORT ze_result_t ZE_APICALL
zelLoaderGetVersions(
   size_t *num_elems,                     //Pointer to num versions to get.  
   zel_component_version_t *versions);    //Pointer to array of versions. If set to NULL, num_elems is returned


#if defined(__cplusplus)
} // extern "C"
#endif
#endif //_ZE_LOADER_H