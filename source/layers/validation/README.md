# Level Zero Validation Layer

## Introduction

The Level Zero driver implementations  [by design](https://oneapi-src.github.io/level-zero-spec/level-zero/latest/core/INTRO.html#error-handling) do minimal error checking and do not guard against invalid API programming.

The Level Zero Validation layer is intended to be the primary Level Zero API error handling mechanism. The validation layer can be enabled at runtime with environment settings. When validation layer is enabled, L0 loader will inject calls to validation layer into L0 API DDI tables. When validation layer is not enabled, it is completely removed from the call path and has no performance cost.  

## Usage

The validation layer is built into a shared library named libze_validation_layer.so or ze_validation_layer.dll. This library must be in your library search path. 

The validation layer can be enabled at runtime by setting `ZE_ENABLE_VALIDATION_LAYER=1`

Level Zero Loader will read this environment settings when either `zeInit` or `zesInit` is called and set up the DDI function pointer tables accordingly. 

By default, no validation modes will be enabled. The individual validation modes must be enabled with the following environment settings:

- `ZE_ENABLE_PARAMETER_VALIDATION`
- `ZE_ENABLE_HANDLE_LIFETIME`
- `ZEL_ENABLE_EVENTS_CHECKER`
- `ZEL_ENABLE_BASIC_LEAK_CHECKER`
- `ZE_ENABLE_THREADING_VALIDATION` (Not yet Implemented)

## Validation Modes

### `ZE_ENABLE_PARAMETER_VALIDATION`

Parameter Validation mode maintains no internal state.  It performs the following checks on each API before calling into driver:
- Non-optional input pointers must not be `nullptr`
- Non-optional input handles must not be `0`
- Input flags must only have valid flag values set
- Input enums values must not be greater than max defined value
- (Planned) `stype` must be set to a valid `ze_structure_type_t` for struct
- (Planned) `pNext` must be `nullptr` or point to a valid extension struct

If a check fails, the appropriate error code is returned and the driver API is not called.

### `ZE_ENABLE_HANDLE_LIFETIME`

This mode maintains an internal mapping of each handle type to a state structure.

- When handle is created it is added to map
- When handle is destroyed it is removed from map
- When application inputs a handle it is validated
- validates handles are properly destroyed
- Additional per handle state checks added as needed
    - Example - Check ze_cmdlist_handle_t open or closed

### `ZEL_ENABLE_EVENTS_CHECKER`

The Events Checker validates usage of events. 
- It is designed to detect potential deadlocks that might occur due to improper event usage in the Level Zero API. It prints out warning messages for user when it detects a potential deadlock.
- In some cases it may also detect whether an event is being used more than once without being reset. Consider a case in which a single event is signaled from twice.

### `ZEL_ENABLE_BASIC_LEAK_CHECKER`

Basic leak checker in the validation layer which tracks the Create and Destroy calls for a given handle type and reports if a create/destroy is missing.


        #### Sample Output

        ```
        ----------------------------------------------------------------------
                       zeContextCreate = 1     \--->        zeContextDestroy = 1
                  zeCommandQueueCreate = 1     \--->   zeCommandQueueDestroy = 1
                        zeModuleCreate = 1     \--->         zeModuleDestroy = 1
                        zeKernelCreate = 1     \--->         zeKernelDestroy = 1
                     zeEventPoolCreate = 1     \--->      zeEventPoolDestroy = 1
          zeCommandListCreateImmediate = 1     |
                   zeCommandListCreate = 1     \--->    zeCommandListDestroy = 1  ---> LEAK = 1
                         zeEventCreate = 2     \--->          zeEventDestroy = 2
                         zeFenceCreate = 1     \--->          zeFenceDestroy = 1
                         zeImageCreate = 0     \--->          zeImageDestroy = 0
                       zeSamplerCreate = 0     \--->        zeSamplerDestroy = 0
                      zeMemAllocDevice = 0     |
                        zeMemAllocHost = 1     |
                      zeMemAllocShared = 0     \--->               zeMemFree = 1
        ```

### `ZE_ENABLE_THREADING_VALIDATION` (Not yet Implemeneted)

Validates:
- Objects are not concurrently reused in free-threaded API calls



## Testing

There is a small set of negative test cases designed to test the validation layer in the [level zero tests repo](https://github.com/oneapi-src/level-zero-tests/tree/master/negative_tests).   

It is desired to add new unit tests directly into validation layer repo that executes with null driver and does not have additional dependencies.   Help Wanted!

## Contributing

See [CONTRIBUTING](CONTRIBUTING.md) for more information.

