# API Tracing, Loader Implementation

## Introduction
API tracing provides a way for tools to receive notifications of **L0 API** calls made by an application. These notifications are provided via callbacks functions that provide direct access to the input and output parameters which can be viewed and modiied. Tools may also use these notifications as triggers to block and inject new API calls into the command stream, such as __metrics__.

Tracing provides for a tool to create one or more __tracers__.  A __tracer__  is identified by a __tracer handle__, and has associated with it a set of __prologue__ functions for each for  each **L0 API** function that can be invoked at the beginning of  these function calls, and a matching set of __epilogue__ functions that can be invoked at the end of L0 API calls.

In summary, this tracing implementation provides functions to create one or more __tracers__, acquiring a __tracer handle__ for each, then registering a set of __prologue__ and __epilogue__ functions for each __tracer handle__, enabling and disabling a __tracer__, and for destroying a __tracer__.

## Enabling Tracing in the Loader
Tracing is implemented as a layer in the loader.  This tracing layer must be enabled by setting the environment variable **ZE_ENABLE_TRACING_LAYER** to 1.  This environment variable must be defined in the application process's context before that process calls _zeInit()_.

## Tracing API
The API for using this tracing implementation is this header file below.  Please examine that header file for tracing API details.

  `include/level_zero/layers/zel_tracing_api.h`

__zelTracerCreate__ returns a __tracer handle__ representing that __tracer__.  A __tracer__ represents a set of __prolog__ callbacks and __epilog__ callbacks.  See **Creation, Registration, Enabling, Disabling, Destroy** below.

## Callback Structures
The per-**L0-API** function structures used to pass arguments into callback handlers (`..params_t`) are defined in the `ze_api.h.  Only **L0 API** functions declared in `ze_api.h` can be traced.

  `include/level_zero/ze_api.h`

## Prolog/Epilog Structures
The structure used to declare sets of __prologue__ and __epilogue__ callbacks (`zel_core_callbacks_t`) is defined in `zel_tracing_api.h`.  This currently references the `ze_core_callbacks_t` declaration in the `ze_api.h`.  Please use the `zel_core_callbacks_t` definition.

  `include/level_zero/layers/zel_tracing_api.h`

## Creation
Users of tracing must first create one or more __tracers__, using __zelTracerCreate__

## Registration
Users of tracing may independently register for enter and exit callbacks for individual **L0 AP**I calls. These callbacks associated with a __tracer handle__ returned from the __zelTracerCreate__.  The set of __tracers__ apply across all drivers and devices.

- __zelTracerSetPrologues__ is used to specify all the enter callbacks for a __tracer handle__.

- __zelTracerSetEpilogues__ is used to specify all the exit callbacks for a __tracer handle__.

  If the value of a callback is __nullptr__, then it will be ignored. There

  The callbacks are defined as a collection of per-API function pointers, with the following parameters:

    - __params__ : a structure capturing pointers to the input and output parameters of the current instance

    - __result__ : the current value of the return value

    - __pTracerUserData__ : a per-tracer per-API pointer to user's data that is passed into the callback handler functions.

    - __ppTracerInstanceUserData__ : a per-tracer, per-instance, per-thread storage location; typically used for passing data from the prologue to the epilogue.  See example below.

 __ZeInit__ is traceable for all calls subsequent from the creation and enabling of the tracer itself.

## Enabling, Disabling and Destruction
The __tracer__ is created in a disabled state and must be explicitly enabled by calling __zelTracerSetEnabled__. The implementation guarantees that __prologue__ and __epilogue__ handlers for a given **L0 API** function will always be executed in pairs; i.e.

  if the __prologue__ function was called and there is a corresponding __ epilog__ function, then the __epilogue__ is guaranteed to be called, even if another thread disabled the __tracer__ between execution

  if the __prologue__ function was not called then the __epilogue__ function is guaranteed not to be called, even if another thread enabled the tracer between execution

The __tracer__ must be disabled by the application before the __tracer__ is destroyed. If multiple threads are in-flight, then callbacks that are in progress for that __tracer__ will continue to execute even after the __tracer__ is disabled;  The implementation will stall and wait for any outstanding threads executing a __tracer__ __prolog__ or __epilog__  functions to complere those during __zelTracerDestroy__ of that __tracer__.

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

void TracingExample( ... )
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
    prologCbs.CommandList.pfnAppendLaunchFunction = OnEnterCommandListAppendLaunchKernel;
    epilogCbs.CommandList.pfnAppendLaunchFunction = OnExitCommandListAppendLaunchKernel;

    zelTracerSetPrologues(hTracer, &prologCbs);
    zelTracerSetEpilogues(hTracer, &epilogCbs);

    zelTracerSetEnabled(hTracer, true);

    zeCommandListAppendLaunchKernel(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);
    zeCommandListAppendLaunchKernel(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);
    zeCommandListAppendLaunchKernel(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);

    zelTracerSetEnabled(hTracer, false);
    zelTracerDestroy(hTracer);
}
```
