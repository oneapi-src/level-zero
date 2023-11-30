/*
 *
 * Copyright (C) 2019-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#if defined(__cplusplus)
#pragma once
#endif
#include <stdlib.h>
#include <string.h>
#include <string>

///////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32)
#  include <windows.h>
inline void getLastErrorString(std::string &errorValue) {
    DWORD errorID = GetLastError();
    if (errorID) {

        LPSTR tempErrorMessage = nullptr;

        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, errorID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&tempErrorMessage, 0, NULL);

        errorValue.assign(tempErrorMessage);

        LocalFree(tempErrorMessage);
    }
}
#  define MAKE_LIBRARY_NAME(NAME, VERSION)    NAME".dll"
#  define MAKE_LAYER_NAME(NAME)    NAME".dll"
#  define LOAD_DRIVER_LIBRARY(NAME) LoadLibraryExA(NAME, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32)
#  define GET_LIBRARY_ERROR(ERROR_STRING) getLastErrorString(ERROR_STRING)
#  define FREE_DRIVER_LIBRARY(LIB)  FreeLibrary(LIB)
#  define FREE_DRIVER_LIBRARY_FAILURE_CHECK(RESULT)  (RESULT) == 0 ? true : false
#  define GET_FUNCTION_PTR(LIB, FUNC_NAME) GetProcAddress(LIB, FUNC_NAME)
#  define string_copy_s strncpy_s
#else
#  include <dlfcn.h>
#  define HMODULE void*
#  define MAKE_LIBRARY_NAME(NAME, VERSION)    "lib" NAME ".so." VERSION
#  define MAKE_LAYER_NAME(NAME)    "lib" NAME ".so." L0_VALIDATION_LAYER_SUPPORTED_VERSION
#  define LOAD_DRIVER_LIBRARY(NAME) dlopen(NAME, RTLD_LAZY|RTLD_LOCAL)
#  define GET_LIBRARY_ERROR(ERROR_STRING) ERROR_STRING.assign(dlerror())
#  define FREE_DRIVER_LIBRARY(LIB)  dlclose(LIB)
#  define FREE_DRIVER_LIBRARY_FAILURE_CHECK(RESULT)  (RESULT) != 0 ? true : false
#  define GET_FUNCTION_PTR(LIB, FUNC_NAME) dlsym(LIB, FUNC_NAME)
#  define string_copy_s strncpy
#endif

inline std::string create_library_path(const char *name, const char *path){
    std::string library_path;
    if (path && (strcmp("", path) != 0)) {
        library_path.assign(path);
#ifdef _WIN32
        library_path.append("\\");
#else
        library_path.append("/");
#endif
        library_path.append(name);
    } else {
        library_path.assign(name);
    }
    return library_path;
}

#ifdef _WIN32
inline std::string readLevelZeroLoaderLibraryPath() {
    std::string LoaderRegKeyPath = "";
    HKEY regKey = {};
    DWORD regValueType = {};
    DWORD pathSize = {};
    std::string loaderMajorVersionString = std::to_string(LOADER_VERSION_MAJOR);
    std::string loaderRegistryKeyPath = "Software\\Intel\\oneAPI\\LevelZero\\";
    loaderRegistryKeyPath.append(loaderMajorVersionString);
    static constexpr char levelZeroLoaderPathKey[] = "LevelZeroLoaderPath";

    LSTATUS regOpenStatus = RegOpenKeyA(HKEY_LOCAL_MACHINE, loaderRegistryKeyPath.c_str(), &regKey);

    if (ERROR_SUCCESS != regOpenStatus) {
        return LoaderRegKeyPath;
    }

    LSTATUS regOpStatus = RegQueryValueExA(regKey, levelZeroLoaderPathKey, NULL,
                                           &regValueType, NULL, &pathSize);

    if ((ERROR_SUCCESS == regOpStatus) && (REG_SZ == regValueType)) {
        LoaderRegKeyPath.resize(pathSize);
        regOpStatus = RegQueryValueExA(regKey, levelZeroLoaderPathKey, NULL,
                                       &regValueType, (LPBYTE) & *LoaderRegKeyPath.begin(),
                                       &pathSize);
        if (ERROR_SUCCESS != regOpStatus) {
            LoaderRegKeyPath.clear();
            LoaderRegKeyPath.assign("");
        }
    }

    return LoaderRegKeyPath;
}
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
