# oneAPI Level Zero

This repository contains the following components of oneAPI:

- Copies of the Level Zero Specification API C/C++ header files
- Level Zero Loader
- Level Zero Validation Layer
- Level Zero Tracing Layer

This project is part of the larger [oneAPI](https://www.oneapi.com/) project.

See the [oneAPI specification](https://oneapi-spec.uxlfoundation.org/specifications/oneapi/latest/) for more information about the oneAPI project.

See the [Level Zero specification](https://oneapi-src.github.io/level-zero-spec/level-zero/latest/index.html) for more information about Level Zero.

See the [Level Zero specification repo](https://github.com/oneapi-src/level-zero-spec) for contributing to the specification.

Level Zero API versions are listed in the `ze_api_version_t` enumeration, located in the
[ze_api.h](./include/ze_api.h) file.

# Building and Installing

Project is defined using [CMake](https://cmake.org/).

## Linux

```
mkdir build
cd build
cmake .. -D CMAKE_BUILD_TYPE=Release
cmake --build . --target package --parallel $(nproc)
cmake --build . --target install
```

# Static Loader
To build the Loader statically one must set `-DBUILD_STATIC=1` during the cmake configuration step.

The build of the static loader creates a ze_loader.a/.lib which will link the source/lib source code into your application or library.

This enables for inclusion of all L0 symbols into your application/library allowing for backwards compatability with older versions of the Loader.

The static loader "shim" dynamically loads the ze_loader.so/.dll on the system enabling plugin like behavior where the init will fail gracefully given a usable loader or L0 driver is not found.

When the `-DBUILD_STATIC=1` is executed, the dynamic loader and layers are not built to avoid conflicts during local test execution which requires the dynamic loader and layers to all be the same version for compatability.

Testing with the static loader requires a build of the dynamic loader or an installation of the dynamic loader to exist in the library path.

# Debug Trace
The Level Zero Loader has the ability to print warnings and errors which occur within the internals of the Level Zero Loader itself.

To enable this debug tracing feature, set the environment variable `ZE_ENABLE_LOADER_DEBUG_TRACE=1`.

This will enforce the Loader to print all errors whether fatal or non-fatal to stderr with the PREFIX `ZE_LOADER_DEBUG_TRACE:`.


# Logging to File - PREVIEW
The Level Zero Loader uses spdlog logging and can be controlled via environment variables:

`ZEL_ENABLE_LOADER_LOGGING=1`

`ZEL_LOADER_LOG_DIR='/directory/path'`

`ZEL_LOADER_LOGGING_LEVEL=debug`

Default Log Pattern (Does not need to be set, please see below):
`ZEL_LOADER_LOG_PATTERN='[%Y-%m-%d %H:%M:%S.%e] [thread-id: %t] [%^%l%$] %v'`

Valid logging levels are trace, debug, info, warn, error, critical, off.
Logging is disabled by default but when enabled the default level is 'warn'.
The default log file is 'ze_loader.log' in '.oneapi_logs' in the current
user's home directory.

The default log pattern includes timestamps, thread IDs, log levels, and messages.
You can customize the pattern using `ZEL_LOADER_LOG_PATTERN`. Common pattern flags:
- `%t` - thread id
- `%Y-%m-%d %H:%M:%S.%e` - timestamp with milliseconds
- `%l` - log level
- `%v` - the actual log message
See spdlog documentation for more pattern options.

This feature is in early development and is preview only.

# Logging API calls
The Level Zero Loader will log all API calls whenever logging level is set to `trace` and
validation layer is enabled. Following variables need to be set to enable API logging:

`ZEL_ENABLE_LOADER_LOGGING=1`

`ZEL_LOADER_LOGGING_LEVEL=trace`

`ZE_ENABLE_VALIDATION_LAYER=1`

By default logs will be written to the log file, as described above. To print the logs
to stderr instead, `ZEL_LOADER_LOG_CONSOLE=1` needs to be set.

The API logging output format includes both function entry and exit information, showing parameter names on entry and parameter values with the result code on exit. Each log entry is timestamped and includes the thread-id, logger name, log level. Example output:

```
[2026-02-13 18:51:29.960] [thread-id: 3139] [trace] zeDriverGet(pCount, phDrivers)
[2026-02-13 18:51:29.960] [thread-id: 3139] [trace] SUCCESS (ZE_RESULT_SUCCESS) in zeDriverGet(pCount=1, phDrivers=nullptr)
[2026-02-13 18:51:29.960] [thread-id: 3139] [trace] zeDriverGet(pCount, phDrivers)
[2026-02-13 18:51:29.960] [thread-id: 3139] [trace] SUCCESS (ZE_RESULT_SUCCESS) in zeDriverGet(pCount=1, phDrivers=0x5651c11920f0)
[2026-02-13 18:51:29.961010] [0x00007f5d45f57780] [info]    Default Driver retrieved at index 0
[2026-02-13 18:51:29.961] [thread-id: 3139] [trace] zeContextCreate(hDriver, desc, phContext)
[2026-02-13 18:51:29.961] [thread-id: 3139] [trace] SUCCESS (ZE_RESULT_SUCCESS) in zeContextCreate(hDriver=0x5651c1166418, desc={stype=0x7ffdb52dc060, flags=0}, phContext=0x5651c0276c48)
[2026-02-13 18:51:29.962] [thread-id: 3139] [trace] zeDeviceGet(hDriver, pCount, phDevices)
[2026-02-13 18:51:29.962] [thread-id: 3139] [trace] SUCCESS (ZE_RESULT_SUCCESS) in zeDeviceGet(hDriver=0x5651c1166418, pCount=2, phDevices=nullptr)
[2026-02-13 18:51:29.962] [thread-id: 3139] [trace] zeDeviceGet(hDriver, pCount, phDevices)
[2026-02-13 18:51:29.962] [thread-id: 3139] [trace] SUCCESS (ZE_RESULT_SUCCESS) in zeDeviceGet(hDriver=0x5651c1166418, pCount=2, phDevices=0x5651c1192230)
[2026-02-13 18:51:29.962] [thread-id: 3139] [trace] zeDeviceGet(hDriver, pCount, phDevices)
[2026-02-13 18:51:29.962] [thread-id: 3139] [trace] SUCCESS (ZE_RESULT_SUCCESS) in zeDeviceGet(hDriver=0x5651c1166418, pCount=2, phDevices=nullptr)
[2026-02-13 18:51:29.962692] [0x00007f5d45f57780] [info]    Default Device retrieved at index 0
[2026-02-13 18:51:29.963] [thread-id: 3139] [trace] zeCommandQueueCreate(hContext, hDevice, desc, phCommandQueue)
[2026-02-13 18:51:29.963] [thread-id: 3139] [trace] SUCCESS (ZE_RESULT_SUCCESS) in zeCommandQueueCreate(hContext=0x5651c0276c48, hDevice=0x5651c1166778, desc={stype=0x7ffdb52dbf90, ordinal=0, index=0, flags=0, mode=0x7ffdb52dbfac, priority=0x7ffdb52dbfb0}, phCommandQueue=0x5651c1192748)
[2026-02-13 18:51:29.963] [thread-id: 3139] [trace] zeCommandListCreate(hContext, hDevice, desc, phCommandList)
[2026-02-13 18:51:29.964] [thread-id: 3139] [trace] SUCCESS (ZE_RESULT_SUCCESS) in zeCommandListCreate(hContext=0x5651c0276c48, hDevice=0x5651c1166778, desc={stype=0x7ffdb52dbf70, commandQueueGroupOrdinal=0, flags=0}, phCommandList=0x5651c119af68)
[2026-02-13 18:51:29.965] [thread-id: 3139] [trace] zeMemOpenIpcHandle(hContext, hDevice, handle, flags, pptr)
```



# Driver/Device Sorting

As of v1.20.3 of the Loader, Drivers and Devices reported to the user are sorted to enable the first device to be the best available device.

- By default, drivers will be sorted such that the ordering will be:
    - Drivers with Discrete GPUs only
    - Drivers with Discrete and Integrated GPUs
    - Drivers with Integrated GPUs
    - Drivers with Mixed Devices Types (ie GPU + NPU)
    - Drivers with Non GPU Devices Only
- If ZE_ENABLE_PCI_ID_DEVICE_ORDER is set, then the following ordering
  is provided:
    - Drivers with Integrated GPUs
    - Drivers with Discrete and Integrated GPUs
    - Drivers with Discrete GPUs only
    - Drivers with Mixed Devices Types (ie GPU + NPU)
    - Drivers with Non GPU Devices Only

The order of the sorting is based on the enumerator:
`zel_driver_type_t`

The ordering of the drivers reported to the user is based on the order of the enumerations provided.
When additional driver types are added, they should be added to the end of the list to avoid reporting new device types
before known device types.

NOTE: Due to known issues with Program Instrumentation usecases, when ZET_ENABLE_PROGRAM_INSTRUMENTATION is enabled, driver sorting is not possible in the loader.

## Windows
Use Microsoft* Visual Studio x64 command prompt to run the following commands and build the project:
```sh
mkdir build
cd build
cmake -G "NMake Makefiles" CMAKE_CXX_FLAGS="/EHsc" ..
nmake
```


# Contributing

See [CONTRIBUTING](CONTRIBUTING.md) for more information.

# License

Distributed under the MIT license. See [LICENSE](LICENSE) for more information.

# Security

See Intel's [Security Center](https://www.intel.com/content/www/us/en/security-center/default.html) for information on how to report a potential security issue or vulnerability.

See also [SECURITY](SECURITY.md).
