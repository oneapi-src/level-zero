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
#  define GET_FUNCTION_PTR(LIB, FUNC_NAME) reinterpret_cast<void *>(GetProcAddress(LIB, FUNC_NAME))
#  define string_copy_s strncpy_s
#  define putenv_safe _putenv
#  define strdup_safe _strdup
#else
#  include <link.h>
#  include <dlfcn.h>
#  define HMODULE void*
#  define LOAD_DRIVER_LIBRARY(NAME) dlopen(NAME, RTLD_LAZY|RTLD_LOCAL)
#  define GET_LIBRARY_ERROR(ERROR_STRING) ERROR_STRING.assign(dlerror())
#  define FREE_DRIVER_LIBRARY(LIB)  dlclose(LIB)
#  define FREE_DRIVER_LIBRARY_FAILURE_CHECK(RESULT)  (RESULT) != 0 ? true : false
#  define GET_FUNCTION_PTR(LIB, FUNC_NAME) dlsym(LIB, FUNC_NAME)
#  define string_copy_s strncpy
#  define putenv_safe putenv
#  define strdup_safe strdup
#endif

#if defined(ANDROID)
#  define MAKE_LIBRARY_NAME(NAME, VERSION)    "lib" NAME ".so"
#  define MAKE_LAYER_NAME(NAME)    "lib" NAME ".so"
#elif !defined(WIN32)
#  define MAKE_LIBRARY_NAME(NAME, VERSION)    "lib" NAME ".so." VERSION
#  define MAKE_LAYER_NAME(NAME)    "lib" NAME ".so." L0_VALIDATION_LAYER_SUPPORTED_VERSION
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

// Reads a single Level Zero loader setting from the given registry root under
// the "Environment" subkey of the loader key. Value names match the
// corresponding environment variable names (e.g. "ZEL_LOADER_LOG_CONSOLE").
// Supports REG_SZ / REG_EXPAND_SZ (used verbatim) and REG_DWORD (rendered as a
// decimal string) so that numeric flags can be stored either way. Returns true
// and populates 'value' when the named value exists and is of a supported type.
inline bool readLoaderSettingFromRegistryRoot(HKEY root, const char* name, std::string& value) {
    static constexpr char settingsKeyPath[] = "Software\\Intel\\oneAPI\\LevelZero\\Environment";

    HKEY regKey = {};
    if (ERROR_SUCCESS != RegOpenKeyExA(root, settingsKeyPath, 0, KEY_QUERY_VALUE, &regKey)) {
        return false;
    }

    DWORD regValueType = {};
    DWORD dataSize = {};
    bool found = false;
    LSTATUS regOpStatus = RegQueryValueExA(regKey, name, NULL, &regValueType, NULL, &dataSize);

    if (ERROR_SUCCESS == regOpStatus) {
        if ((REG_SZ == regValueType || REG_EXPAND_SZ == regValueType) && dataSize > 0) {
            std::string buffer(dataSize, '\0');
            regOpStatus = RegQueryValueExA(regKey, name, NULL, &regValueType,
                                           (LPBYTE) & *buffer.begin(), &dataSize);
            if (ERROR_SUCCESS == regOpStatus) {
                // dataSize includes the terminating null for string types; trim
                // at the first null so 'value' holds a clean C-string.
                value.assign(buffer.c_str());
                found = true;
            }
        } else if (REG_DWORD == regValueType && dataSize == sizeof(DWORD)) {
            DWORD dwordValue = 0;
            regOpStatus = RegQueryValueExA(regKey, name, NULL, &regValueType,
                                           (LPBYTE)&dwordValue, &dataSize);
            if (ERROR_SUCCESS == regOpStatus) {
                value.assign(std::to_string(dwordValue));
                found = true;
            }
        }
    }

    RegCloseKey(regKey);
    return found;
}

// Fallback lookup for loader settings on Windows: checks the current user hive
// first (HKEY_CURRENT_USER, writable without administrator rights) and then the
// machine-wide hive (HKEY_LOCAL_MACHINE). This lets loader environment settings
// be configured persistently in the registry for processes (e.g. GUI apps and
// their child processes) that cannot conveniently inherit them from the shell.
inline bool readLoaderSettingFromRegistry(const char* name, std::string& value) {
    if (readLoaderSettingFromRegistryRoot(HKEY_CURRENT_USER, name, value)) {
        return true;
    }
    return readLoaderSettingFromRegistryRoot(HKEY_LOCAL_MACHINE, name, value);
}
#endif

// Looks up a loader setting by name. The process environment always takes
// precedence; on Windows, if the variable is not present in the environment the
// registry fallback (see readLoaderSettingFromRegistry) is consulted. Returns
// true and populates 'value' when a value is found from either source.
inline bool getenv_raw(const char* name, std::string& value) {
#if defined(_WIN32)
    // Query the required buffer size (includes the terminating null); a return
    // of 0 means the variable is not set in the environment.
    DWORD required = GetEnvironmentVariableA(name, nullptr, 0);
    if (0 != required) {
        std::string buffer(required, '\0');
        DWORD written = GetEnvironmentVariableA(name, &buffer[0], required);
        if (0 != written && written < required) {
            buffer.resize(written);
            value.assign(std::move(buffer));
            return true;
        }
    }
    return readLoaderSettingFromRegistry(name, value);
#else
    const char* env = getenv(name);
    if (nullptr == env) {
        return false;
    }
    value.assign(env);
    return true;
#endif
}

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
    std::string value;
    if( !getenv_raw( name, value ) || ( "0" == value ) )
        return false;
    return ( "1" == value );
}

// Returns the numeric mode (0, 1, or 2) for env vars that support a two-level
// flag scheme: 0 = off, 1 = legacy/normal, 2 = advanced/verbose.
// Any value other than "1" or "2" is treated as 0.
inline uint32_t getenv_tomode( const char* name )
{
    std::string value;
    if (!getenv_raw(name, value) || value == "0")
        return 0;
    if (value == "2")
        return 2;
    if (value == "1")
        return 1;
    return 0;
}


inline std::string getenv_string ( const char* name){
    std::string value;
    if (!getenv_raw(name, value))
        return "";
    return value;
}
