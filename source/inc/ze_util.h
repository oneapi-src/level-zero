/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#if defined(__cplusplus)
#pragma once
#endif
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32)
#  include <Windows.h>
#  define MAKE_LIBRARY_NAME(NAME, VERSION)    NAME".dll"
#  define MAKE_LAYER_NAME(NAME)    NAME".dll"
#  define LOAD_DRIVER_LIBRARY(NAME) LoadLibrary(NAME)
#  define FREE_DRIVER_LIBRARY(LIB)  if(LIB) FreeLibrary(LIB)
#  define GET_FUNCTION_PTR(LIB, FUNC_NAME) GetProcAddress(LIB, FUNC_NAME)
#else
#  include <dlfcn.h>
#  define HMODULE void*
#  define MAKE_LIBRARY_NAME(NAME, VERSION)    "lib" NAME ".so." VERSION
#  define MAKE_LAYER_NAME(NAME)    "lib" NAME ".so." L0_VALIDATION_LAYER_SUPPORTED_VERSION
#  define LOAD_DRIVER_LIBRARY(NAME) dlopen(NAME, RTLD_LAZY|RTLD_LOCAL|RTLD_DEEPBIND)
#  define FREE_DRIVER_LIBRARY(LIB)  if(LIB) dlclose(LIB)
#  define GET_FUNCTION_PTR(LIB, FUNC_NAME) dlsym(LIB, FUNC_NAME)
#endif

//////////////////////////////////////////////////////////////////////////
#if !defined(_WIN32) && (__GNUC__ >= 4)
#define __zedlllocal  __attribute__ ((visibility ("hidden")))
#else
#define __zedlllocal
#endif

///////////////////////////////////////////////////////////////////////////////
#if ZE_ENABLE_OCL_INTEROP
typedef struct _cl_mem* cl_mem;
typedef struct _cl_command_queue* cl_command_queue;
typedef struct _cl_context* cl_context;
typedef struct _cl_program* cl_program;
#endif

///////////////////////////////////////////////////////////////////////////////
inline bool getenv_tobool( const char* name )
{
    const char* env = nullptr;

#if defined(_WIN32)
    char buffer[8];
    auto rc = GetEnvironmentVariable(name, buffer, 8);
    if (0 != rc && rc <= 8) {
        env = buffer;
    }
#else
    env = getenv(name);
#endif

    if( ( nullptr == env ) || ( 0 == strcmp( "0", env ) ) )
        return false;
    return ( 0 == strcmp( "1", env ) );
}
