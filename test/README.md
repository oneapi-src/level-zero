# Level Zero Loader Unit Tests

This directory contains unit tests for the Level Zero Loader, built using Google Test (gtest) and executed through CMake's CTest framework.

## Overview

The test suite validates the following components:
- **Loader API**: Core loader functionality and version queries
- **Driver Initialization**: Driver discovery, initialization, and ordering
- **Validation Layer**: Parameter validation and error detection
- **Tracing Layer**: API call tracing and callback mechanisms
- **Multi-Driver Support**: Multiple driver scenarios and interactions
- **Sysman APIs**: System management API conformance
- **Handle Translation**: Loader handle translation mechanisms

## Test Structure

### Test Executable

All tests are compiled into a single executable named `tests`, which includes:
- `loader_api.cpp` - General loader API tests
- `loader_validation_layer.cpp` - Validation layer tests
- `loader_tracing_layer.cpp` - Tracing layer tests
- `driver_ordering_helper_tests.cpp` - Driver ordering helper functions
- `driver_ordering_unit_tests.cpp` - Driver ordering logic (static builds and non-Windows only)
- `driver_teardown_unit_tests.cpp` - Driver teardown logic (static builds and non-Windows only)
- `init_driver_unit_tests.cpp` - Driver initialization tests (non-Windows only)
- `init_driver_dynamic_unit_tests.cpp` - Dynamic driver initialization tests (dynamic builds, non-Windows only)

### Build Configurations

Different test files are conditionally compiled based on the build configuration:

**Static Build Only (`BUILD_STATIC` or non-Windows):**
- `driver_ordering_unit_tests.cpp`
- `driver_teardown_unit_tests.cpp`

**Non-Windows Only:**
- `init_driver_unit_tests.cpp`

**Dynamic Build + Non-Windows:**
- `init_driver_dynamic_unit_tests.cpp`

These restrictions exist because certain tests require access to internal loader symbols that are not exported in Windows DLLs or depend on platform-specific driver discovery mechanisms.

## Running Tests

### ⚠️ IMPORTANT: Do Not Run Test Binaries Directly

**The test binary should NEVER be run outside of the CTest environment.**

CTest automatically sets up the required environment variables, working directories, and driver paths needed for each test. Running the test executable directly (`./tests` or `./bin/tests`) will result in:
- Missing environment configurations
- Incorrect driver paths
- Failed test assertions
- Unreliable test results

### Prerequisites: Set ZEL_LIBRARY_PATH

**Before running CTest, you must set the `ZEL_LIBRARY_PATH` environment variable** to point to where the loader libraries and null drivers are located. This ensures tests can find the required libraries at runtime.

**Linux/Mac:**
```bash
export ZEL_LIBRARY_PATH=/path/to/build/lib
# or for current build directory:
export ZEL_LIBRARY_PATH=$PWD/lib
```

**Windows:**
```cmd
set ZEL_LIBRARY_PATH=C:\path\to\build\bin\Release
# or for current build directory:
set ZEL_LIBRARY_PATH=%CD%\bin\Release
```

**Example for typical build directory:**
```bash
cd build
export ZEL_LIBRARY_PATH=$PWD/lib
ctest
```

Without this environment variable, tests will fail to locate the loader and driver libraries.

### Running Tests via CTest

**Run all tests:**
```bash
cd build
export ZEL_LIBRARY_PATH=$PWD/lib  # Set library path first
ctest
```

**Run tests with verbose output:**
```bash
ctest --verbose
# or
ctest -V
```

**Run a specific test by name:**
```bash
ctest -R tests_api
ctest -R tests_multi_driver_sort
```

**Run tests matching a pattern:**
```bash
ctest -R "tests_loader_version.*"
ctest -R ".*sysman.*"
```

**List all available tests:**
```bash
ctest -N
```

**Run tests in parallel (4 jobs):**
```bash
ctest -j4
```

**Run tests and show only failures:**
```bash
ctest --output-on-failure
```

## Environment Variables Used in Tests

Tests rely on environment variables to configure the loader behavior. These are automatically set by CTest for each test via the `set_property(TEST ... PROPERTY ENVIRONMENT ...)` directive in CMakeLists.txt.

### Required Environment Variable

| Variable | Purpose | Example Values |
|----------|---------|----------------|
| `ZEL_LIBRARY_PATH` | **Required before running CTest.** Specifies the path to loader libraries and null drivers | `$PWD/lib` (Linux), `%CD%\bin\Release` (Windows) |

### Core Environment Variables

| Variable | Purpose | Common Values |
|----------|---------|---------------|
| `ZE_ENABLE_LOADER_DEBUG_TRACE` | Enable debug tracing output from the loader | `1` (enabled) |
| `ZE_ENABLE_NULL_DRIVER` | Enable the null (test) driver | `1` (enabled) |
| `ZE_ENABLE_ALT_DRIVERS` | Specify alternative driver paths for multi-driver testing | Comma-separated paths to driver libraries |
| `ZE_ENABLE_LOADER_DRIVER_DDI_PATH` | Enable DDI extension path support | `1` (enabled) |

### Test-Specific Environment Variables

| Variable | Purpose | Used In |
|----------|---------|---------|
| `ZEL_TEST_NULL_DRIVER_TYPE` | Set the type of null driver for testing | `GPU`, `NPU`, etc. |
| `ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT` | Disable DDI extension in null driver | `1` (single), `3` (both drivers) |
| `ZEL_DRIVERS_ORDER` | Specify driver ordering preference | See [driver ordering documentation](../ZEL_DRIVERS_ORDER_Tests.md) |
| `ZEL_LOADER_LOGGING_ENABLE_SUCCESS_PRINT` | Enable logging of successful API calls | `1` (enabled) |

### Example Environment Setup (Set by CTest)

```cmake
set_property(TEST tests_api PROPERTY ENVIRONMENT 
    "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

set_property(TEST tests_multi_driver_sort PROPERTY ENVIRONMENT 
    "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=/path/to/ze_null_test1.so,/path/to/ze_null_test2.so")
```

## Adding New Tests

### 1. Write Test Code

Create a new test using Google Test macros in an existing `.cpp` file or create a new one:

```cpp
#include "gtest/gtest.h"
#include "ze_api.h"

TEST(MyTestSuite, GivenConditionWhenActionThenExpectedResult) {
    // Setup
    ze_result_t result;
    
    // Execute
    result = zeInit(0);
    
    // Verify
    EXPECT_EQ(ZE_RESULT_SUCCESS, result);
}
```

### 2. Add Source File to CMakeLists.txt (if new file)

If creating a new test file, add it to the test executable:

```cmake
if(NOT WIN32)  # If platform-specific
  target_sources(tests PRIVATE my_new_test.cpp)
endif()
```

### 3. Register Test with CTest

Add the test to CMakeLists.txt using `add_test`:

```cmake
add_test(NAME tests_my_new_feature 
    COMMAND tests --gtest_filter=*MyTestSuite.GivenConditionWhenActionThenExpectedResult*)
set_property(TEST tests_my_new_feature PROPERTY ENVIRONMENT 
    "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")
```

**Key points:**
- Use a descriptive test name prefixed with `tests_`
- Use `--gtest_filter` to target specific tests by pattern
- Set required environment variables with `set_property`
- Multiple environment variables are separated by semicolons

### 4. Build and Run

```bash
cd build
cmake ..
make tests
export ZEL_LIBRARY_PATH=$PWD/lib  # Set library path
ctest -R tests_my_new_feature --verbose
```

## Test Naming Conventions

Tests follow the pattern: `Given[Context]When[Action]Then[Result]`

**Examples:**
- `GivenLevelZeroLoaderPresentWhenCallingzeInitThenExpectSuccess`
- `GivenMultipleDriversWhenCallingZeInitDriversThenExpectSuccessForZeInit`
- `GivenNullPointerWhenCallingzelGetTracingLayerStateThenErrorInvalidNullPointerIsReturned`

This convention makes test intent clear and helps with filtering tests by scenario.

## Common Test Categories

### Loader Version Tests
Test the loader version query APIs:
- `tests_loader_version_*`

### Driver Initialization Tests
Test driver discovery and initialization:
- `tests_init_*`
- `tests_both_init_*`
- `tests_no_initialization`

### Multi-Driver Tests
Test scenarios with multiple drivers loaded:
- `tests_multi_driver_*`
- Uses `ZE_ENABLE_ALT_DRIVERS` to load multiple null drivers

### Driver Ordering Tests
Test the `ZEL_DRIVERS_ORDER` environment variable:
- `tests_driver_ordering_*`
- `driver_ordering_unit_tests`

### Validation Layer Tests
Test parameter validation and error detection:
- `tests_event_deadlock`
- Tests in `loader_validation_layer.cpp`

### Tracing Layer Tests
Test API call tracing functionality:
- `tests_tracing_layer_state_*`
- `test_zer_tracing_*`

### Sysman API Tests
Test System Management API conformance:
- `tests_single_driver_sysman_*`
- `tests_multi_driver_sysman_*`

### Handle Translation Tests
Test loader handle translation mechanisms:
- `tests_loader_translate_handles_*`

## Debugging Tests

### Run a Single Test with Verbose Output
```bash
cd build
export ZEL_LIBRARY_PATH=$PWD/lib  # Set library path first
ctest -R tests_api -V
```

### Use CTest Options for Debugging

CTest provides various options for debugging and controlling test execution:

```bash
# Run with even more verbose output
ctest -VV

# Stop on first failure
ctest --stop-on-failure

# Run only failed tests from last run
ctest --rerun-failed

# Run tests in parallel
ctest -j4

# Show test output only for failures
ctest --output-on-failure
```

**Note:** Always run tests through CTest. Running the test binary directly is not supported and will lead to unreliable results due to missing environment configurations, incorrect driver paths, and other setup that CTest handles automatically.

## Test Fake Drivers

The test suite uses "fake" drivers (copies of the null driver with different names) to simulate multiple driver scenarios:

**Created during build:**
- `ze_fake_gpu.so` / `ze_fake_gpu.dll` - Simulates a GPU driver
- `ze_fake_npu.so` / `ze_fake_npu.dll` - Simulates an NPU driver
- `ze_fake_vpu.so` / `ze_fake_vpu.dll` - Simulates a VPU driver

These are automatically copied from the null driver implementations during the test build process.

## Platform-Specific Notes

### Windows
- Some tests requiring internal symbols are disabled for DLL builds
- Driver paths use backslashes and `.dll` extension
- Environment variables are set differently (handled by CTest)

### Linux
- All tests are available for both static and dynamic builds (when appropriate)
- Driver paths use forward slashes and `.so` extension
- Additional tests for driver discovery mechanisms

## Continuous Integration

Tests are run automatically in CI pipelines on:
- Pull requests
- Commits to main branches
- Release branches

CI runs tests across multiple platforms and configurations to ensure compatibility.

## Troubleshooting

**Problem:** Tests fail with "driver not found" or "library not found" errors  
**Solution:** Ensure `ZEL_LIBRARY_PATH` is set before running CTest:
```bash
export ZEL_LIBRARY_PATH=$PWD/lib  # Linux/Mac
set ZEL_LIBRARY_PATH=%CD%\bin\Release  # Windows
```
Also verify you're running tests via `ctest`, not directly.

**Problem:** Tests pass locally but fail in CI  
**Solution:** Check for platform-specific code or environment assumptions. Ensure tests don't depend on specific hardware.

**Problem:** New test isn't discovered by CTest  
**Solution:** Verify you've called `add_test()` in CMakeLists.txt and rebuilt the project.

**Problem:** Test requires specific environment variable  
**Solution:** Add the variable using `set_property(TEST ... PROPERTY ENVIRONMENT ...)` in CMakeLists.txt.

## Additional Resources

- [Google Test Documentation](https://google.github.io/googletest/)
- [CMake CTest Documentation](https://cmake.org/cmake/help/latest/manual/ctest.1.html)
- [Level Zero Specification](https://oneapi-src.github.io/level-zero-spec/level-zero/latest/index.html)
- [Loader API Documentation](../doc/loader_api.md)
