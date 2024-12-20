# oneAPI Level Zero

This repository contains the following components of oneAPI:

- Copies of the Level Zero Specification API C/C++ header files
- Level Zero Loader
- Level Zero Validation Layer
- Level Zero Tracing Layer

This project is part of the larger [oneAPI](https://www.oneapi.com/) project.

See the [oneAPI specification](https://spec.oneapi.com/versions/latest/introduction.html) for more information about the oneAPI project.

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
cmake --build . --target package
cmake --build . --target install
```

# Debug Trace
The Level Zero Loader has the ability to print warnings and errors which occur within the internals of the Level Zero Loader itself.

To enable this debug tracing feature, set the environment variable `ZE_ENABLE_LOADER_DEBUG_TRACE=1`.

This will enforce the Loader to print all errors whether fatal or non-fatal to stderr with the PREFIX `ZE_LOADER_DEBUG_TRACE:`.


# Logging to File - PREVIEW
The Level Zero Loader uses spdlog logging and can be controlled via environment variables:

`ZEL_ENABLE_LOADER_LOGGING=1`

[DEPRECATED] `ZEL_LOADER_LOG_FILE=/path/to/logfile`

`ZEL_LOADER_LOG_DIR='/directory/path'`

`ZEL_LOADER_LOGGING_LEVEL=debug`

Valid logging levels are trace, debug, info, warn, error, critical, off.
Logging is disabled by default but when enabled the default level is 'warn'.
The default log file is 'ze_loader.log' in '.oneapi_logs' in the current
user's home directory.

This feature is in early development and is preview only.


# Contributing

See [CONTRIBUTING](CONTRIBUTING.md) for more information.

# License

Distributed under the MIT license. See [LICENSE](LICENSE) for more information.

# Security

See Intel's [Security Center](https://www.intel.com/content/www/us/en/security-center/default.html) for information on how to report a potential security issue or vulnerability.

See also [SECURITY](SECURITY.md).
