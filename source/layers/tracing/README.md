# API Tracing, Loader Implementation

## Introduction
API tracing provides a way for tools to receive notifications of **L0 API** calls made by an application. These notifications are provided via callback functions that provide direct access to the input and output parameters which can be viewed and modified. Tools may also use these notifications as triggers to block and inject new API calls into the command stream, such as __metrics__.

Tracing provides for a tool to create one or more __tracers__.  A __tracer__  is identified by a __tracer handle__, and has associated with it a set of __prologue__ functions for each **L0 API** function that can be invoked at the beginning of  these function calls, and a matching set of __epilogue__ functions that can be invoked at the end of L0 API calls.

In summary, this tracing implementation provides functions to create one or more __tracers__, acquiring a __tracer handle__ for each, then registering a set of __prologue__ and __epilogue__ functions for each __tracer handle__, enabling and disabling a __tracer__, and for destroying a __tracer__.

## Enabling Tracing in the Loader
Tracing is implemented as a layer in the loader.  This tracing layer must be enabled by setting the environment variable **ZE_ENABLE_TRACING_LAYER** to 1.  This environment variable must be defined in the application process's context before that process calls _zeInit()_.

## Tracing API
The API for using this tracing implementation is this header file below.  Please examine that header file for tracing API details.

  `include/level_zero/layers/zel_tracing_api.h`

__zelTracerCreate__ returns a __tracer handle__ representing that __tracer__.  A __tracer__ represents a set of __prologue__ callbacks and __epilogue__ callbacks.  See **Creation, Registration, Enabling, Disabling and Destruction** below.

## Callback Structures
The per-**L0-API** function structures used to pass arguments into callback handlers (`..params_t`) are defined in the `ze_api.h`.  Only **L0 API** functions declared in `ze_api.h` can be traced.

  `include/level_zero/ze_api.h`

## Prologue/Epilogue Structures
The structure used to declare sets of __prologue__ and __epilogue__ callbacks (`zel_core_callbacks_t`) is defined in `zel_tracing_api.h`.  This currently references the `ze_core_callbacks_t` declaration in `ze_api.h`.  Please use the `zel_core_callbacks_t` definition.

  `include/level_zero/layers/zel_tracing_api.h`

## Creation
Users of tracing must first create one or more __tracers__, using __zelTracerCreate__.

## Registration
Users of tracing may independently register for enter and exit callbacks for individual **L0 API** calls. These callbacks are associated with a __tracer handle__ returned from the __zelTracerCreate__.  The set of __tracers__ applies across all drivers and devices.  There are now TWO classes of interfaces for registering callbacks:

### Registration functions that take a `zet_core_callbacks_t` argument

For this class of registration functions, the `zet_core_callbacks_t` argument is a structure of pointers to callback handler functions.  A __nullptr__ value for one of these entries means no callback handler is defined for the corresponding **L0 API** function.

This `zet_core_callbacks_t` structure is not extensible in a way that could support binary compatibility as new APIs are added to the **L0 specification**.  As a consequence, these registration functions are deprecated and will be removed in the future.  The definition of the `zet_core_callbacks_t` structure is frozen as of the **L0 API 1.0** specification.  Any new **L0 API** functions added since version 1.0 will not be traceable using these registration functions.

- __zelTracerSetPrologues__ is used to specify all the enter callbacks for a __tracer handle__.

- __zelTracerSetEpilogues__ is used to specify all the exit callbacks for a __tracer handle__.

These functions can be called only when the tracer specified by __tracer handle__ is in the disabled state. See **Enabling, Disabling and Destruction** below.

### A set of unique registration function for each API function

A new set of registration functions has been added, one for each **L0 API** function.  These registration  functions have the general form:

-__zelTracerXRegisterCallback(zel_tracer_handle_t hTracer, zel_tracer_reg_t callback_type, ze_pfnXCb_t callback_handler_function)__

The `zel_tracer_reg_t` value can be either `ZEL_REGISTER_PROLOGUE` or `ZEL_REGISTER_EPILOGUE`, specifying whether a prologue or an epilogue handler is being registered.
These new registration functions are defined in the header file `include/level_zero/layers/tracing/zel_tracing_register_cb.h`.  This header file also includes prototypes for callback handler functions and `Xcb_t` structure declarations for **L0 API** functions that have been added since specification version 1.0. When the older __zelTracerSetPrologues__ and __zelTracerSetEpilogues__ functions are removed, the `zet_core_callbacks_t` structure will also be removed, and all __ze_pfnXCb_t__ and `XCb_t` declarations that are in `ze_api.h` will be relocated into this header file.

If the __callback_handler_function__ pointer is NULL, then no callback handler will be registered for that API function.

These register callback functions can be called only when the __hTracer__ argument references a tracer that is in the disabled state.

## Reset All Callbacks

__zelTracerResetAllCallbacks(zel_tracer_handle_t hTracer)__ can be used to set ALL prologue and epilogue callback handlers to NULL.

## Callback Handlers

Callback handlers are functions that are implemented by the application, and registered through either the set epilogue/set prologue functions, or the RegisterCallback APIs.  The `ze_api.h` header file or the `zel_tracing_register_cb.h` header file contain prototype declarations for these functions. Generally, these functions take the following parameters:

    - __params__ : a structure capturing pointers to the input and output parameters of the current instance.

    - __result__ : the current value of the return value.

    - __pTracerUserData__ : a per-tracer per-API pointer to user's data that is passed into the callback handler functions.

    - __ppTracerInstanceUserData__ : a per-tracer, per-instance, per-thread storage location; typically used for passing data from the prologue to the epilogue. See example below.

##  __ZeInit__ is traceable for all calls subsequent from the creation and enabling of the tracer itself.

## Enabling, Disabling and Destruction
The __tracer__ is created in a disabled state and must be explicitly enabled by calling __zelTracerSetEnabled__. The implementation guarantees that __prologue__ and __epilogue__ handlers for a given **L0 API** function will always be executed in pairs; i.e.

- if the __prologue__ function was called and there is a corresponding __epilogue__ function, then the __epilogue__ is guaranteed to be called, even if another thread disabled the __tracer__ between execution

- if the __prologue__ function was not called then the __epilogue__ function is guaranteed not to be called, even if another thread enabled the tracer between execution

The __tracer__ must be disabled by the application before the __tracer__ is destroyed. If multiple threads are in-flight, then callbacks that are in progress for that __tracer__ will continue to execute even after the __tracer__ is disabled; the implementation will stall and wait for any outstanding threads executing a __tracer__ __prologue__ or __epilogue__ functions to complete those during __zelTracerDestroy__ of that __tracer__.

The following pseudo-code demonstrates a basic usage of API tracing:
```
#include "level_zero/ze_api.h"
#include "level_zero/layers/zel_tracing_api.h"

typedef struct _my_tracer_data_t
{
    uint32_t instance;
} my_tracer_data_t;

typedef struct _my_instance_data_t
{
    clock_t start;
} my_instance_data_t;

void OnEnterCommandListAppendLaunchKernel(
    ze_command_list_append_launch_kernel_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData )
{
    my_instance_data_t* instance_data = malloc( sizeof(my_instance_data_t) );
    *ppTracerInstanceUserData = instance_data;

    instance_data->start = clock();
}

void OnExitCommandListAppendLaunchKernel(
    ze_command_list_append_launch_kernel_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData )
{
    clock_t end = clock();

    my_tracer_data_t* tracer_data = (my_tracer_data_t*)pTracerUserData;
    my_instance_data_t* instance_data = (my_instance_data_t*)ppTracerInstanceUserData;

    float time = 1000.f * ( end - instance_data->start ) / CLOCKS_PER_SEC;
    printf("zeCommandListAppendLaunchKernel #%d takes %.4f msn", tracer_data->instance++, time);

    free(instance_data);
}

// An example using deprecated setepilogue/setprologue functions
void TracingExample1( ... )
{
    my_tracer_data_t tracer_data = {};
    zel_tracer_desc_t tracer_desc;
    tracer_desc.stype = ZEL_STRUCTURE_TYPE_TRACER_DESC;
    tracer_desc.pUserData = &tracer_data;
    zel_tracer_handle_t hTracer;
    zelTracerCreate(hDevice, &tracer_desc, &hTracer);

    // Set all callbacks
    zel_core_callbacks_t prologCbs = {};
    zel_core_callbacks_t epilogCbs = {};
    prologCbs.CommandList.pfnAppendLaunchKernelCb = OnEnterCommandListAppendLaunchKernel;
    epilogCbs.CommandList.pfnAppendLaunchKernelCb = OnExitCommandListAppendLaunchKernel;

    zelTracerSetPrologues(hTracer, &prologCbs);
    zelTracerSetEpilogues(hTracer, &epilogCbs);

    zelTracerSetEnabled(hTracer, true);

    zeCommandListAppendLaunchKernel(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);

    zelTracerSetEnabled(hTracer, false);
    zelTracerDestroy(hTracer);
}

// an example using RegisterCallback functions
void TracingExample2( ... )
{
    my_tracer_data_t tracer_data = {};
    zel_tracer_desc_t tracer_desc;
    tracer_desc.stype = ZEL_STRUCTURE_TYPE_TRACER_DESC;
    tracer_desc.pUserData = &tracer_data;
    zel_tracer_handle_t hTracer;
    zelTracerCreate(hDevice, &tracer_desc, &hTracer);

    zelTracerCommandListAppendLaunchKernelRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE, OnEnterCommandListAppendLaunchKernel);
    zelTracerCommandListAppendLaunchKernelRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE, OnExitCommandListAppendLaunchKernel);

    zelTracerSetEnabled(hTracer, true);

    zeCommandListAppendLaunchKernel(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);

    zelTracerSetEnabled(hTracer, false);
    zelTracerDestroy(hTracer);
}
```
