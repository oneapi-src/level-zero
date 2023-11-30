# Level Zero Validation Layer

## Introduction

The Level Zero driver implementations  [by design](https://spec.oneapi.io/level-zero/latest/core/INTRO.html#error-handling) do minimal error checking and do not guard against invalid API programming. 

The Level Zero Validation layer is intended to be the primary Level Zero API error handling mechanism. The validation layer can be enabled at runtime with environment settings. When validation layer is enabled, L0 loader will inject calls to validation layer into L0 API DDI tables. When validation layer is not enabled, it is completely removed from the call path and has no performance cost.  

## Usage

The validation layer is built into a shared library named libze_validation_layer.so or ze_validation_layer.dll. This library must be in your library search path. 

The validation layer can be enabled at runtime by setting `ZE_ENABLE_VALIDATION_LAYER=1`

Level Zero Loader will read this environment settings when either `zeInit` or `zesInit` is called and set up the DDI function pointer tables accordingly. 

By default, no validation modes will be enabled. The individual validation modes must be enabled with the following environment settings:

- `ZE_ENABLE_PARAMETER_VALIDATION`
- `ZE_ENABLE_HANDLE_LIFETIME`
- `ZE_ENABLE_MEMORY_TRACKER` (Not yet Implemeneted)
- `ZE_ENABLE_THREADING_VALIDATION` (Not yet Implemeneted)


## Validation Modes

### `ZE_ENABLE_ALL_VALIDATION`
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


### `ZE_ENABLE_THREADING_VALIDATION` (Not yet Implemeneted)

Validates:
- Objects are not concurrently reused in free-threaded API calls



## Testing

There is a small set of negative test cases designed to test the validation layer in the [level zero tests repo](https://github.com/oneapi-src/level-zero-tests/tree/master/negative_tests).   

It is desired to add new unit tests directly into validation layer repo that executes with null driver and does not have additional dependencies.   Help Wanted!

## Contributing

Pull requests are encouraged!

Please follow the recommended guidelines:

1) All additions must fit inside one of the currently defined validation modes.  Requests for new validation modes can be raised in issues

