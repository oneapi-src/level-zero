# API Tracing, Loader Implementation

## Introduction
API tracing provides a way for tools to receive notifications of **L0 API** calls made by an application. These notifications are provided via callback functions that provide direct access to the input and output parameters which can be viewed and modified. Tools may also use these notifications as triggers to block and inject new API calls into the command stream, such as __metrics__.

Tracing provides for a tool to create one or more __tracers__.  A __tracer__  is identified by a __tracer handle__, and has associated with it a set of __prologue__ functions for each **L0 API** function that can be invoked at the beginning of  these function calls, and a matching set of __epilogue__ functions that can be invoked at the end of L0 API calls.

In summary, this tracing implementation provides functions to create one or more __tracers__, acquiring a __tracer handle__ for each, then registering a set of __prologue__ and __epilogue__ functions for each __tracer handle__, enabling and disabling a __tracer__, and for destroying a __tracer__.

## Enabling Tracing in the Loader
Tracing is implemented as a layer in the loader. There are two ways to enable the tracing layer:

### Static Tracing Layer Enablement (Environment Variable)
The tracing layer can be enabled for the entire process runtime by setting the environment variable **ZE_ENABLE_TRACING_LAYER** to 1. This environment variable must be defined in the application process's context before that process calls _zeInitDrivers()_. When enabled this way, the tracing layer remains active for the entire duration of the application.

### Dynamic Tracing Layer Enablement (Runtime Control)
The tracing layer can also be enabled and disabled dynamically at runtime using the following APIs:

- **zelEnableTracingLayer()** - Enables the tracing layer at runtime. Can be called at any point during application execution, but will only affect subsequent API calls made after the call to this function.

- **zelDisableTracingLayer()** - Disables the tracing layer at runtime. After calling this function, subsequent API calls will not be intercepted by the tracing layer.

- **zelGetTracingLayerState(bool* enabled)** - Queries the current state of the tracing layer. Sets the boolean pointed to by `enabled` to `true` if the tracing layer is currently active, or `false` if it is disabled.

These functions are defined in `include/loader/ze_loader.h`.

Dynamic tracing control provides the flexibility to:
- Enable tracing only for specific regions of code
- Reduce performance overhead by disabling tracing when not needed
- Programmatically control tracing based on runtime conditions

### Tracing Layer vs Tracer Enable/Disable

It is important to understand the distinction between **enabling/disabling the tracing layer** and **enabling/disabling individual tracers**:

#### Tracing Layer Enable/Disable
- Controls whether the tracing layer infrastructure is active in the loader
- Affects **all** Level Zero API calls globally
- When the tracing layer is disabled, **no** API calls are intercepted regardless of individual tracer states
- Controlled via `zelEnableTracingLayer()`, `zelDisableTracingLayer()`, and the `ZE_ENABLE_TRACING_LAYER` environment variable
- Represents a global on/off switch for the entire tracing infrastructure

#### Individual Tracer Enable/Disable
- Controls whether a specific tracer's callbacks are invoked
- Requires the tracing layer to be enabled first
- Controlled via `zelTracerSetEnabled()` for each tracer handle
- Multiple tracers can coexist, each with their own enabled/disabled state
- A tracer being enabled has no effect if the tracing layer itself is disabled

**In summary:**
- The **tracing layer** must be enabled for any tracing to occur
- Individual **tracers** must also be enabled for their callbacks to be invoked
- Disabling the tracing layer stops all tracing regardless of individual tracer states
- When the tracing layer is enabled, only those tracers that are also enabled will have their callbacks invoked

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

### Registering callbacks for driver extension functions

Extension functions retrieved by name via __zeDriverGetExtensionFunctionAddress__ return a raw driver function pointer that the application calls directly. These calls bypass the loader — and therefore the per-API tracing interceptors described above — so they cannot be traced with the core registration functions. To trace them, use:

- __zelTracerDriverExtensionRegisterCallback(zel_tracer_handle_t hTracer, ze_driver_handle_t hDriver, const char\* functionName, zel_tracer_reg_t callback_type, zel_pfnDriverExtensionFunctionCb_t pCallback)__

This registers a prologue or epilogue handler on __hTracer__ for the extension function named __functionName__ on driver __hDriver__. It is declared in `include/loader/ze_loader.h`.

Key points:
- Registration is keyed by the (__hDriver__, __functionName__) pair and is order-independent relative to __zeDriverGetExtensionFunctionAddress__: it takes effect on the next invocation of the function even if the application already cached the function pointer.
- `callback_type` is `ZEL_REGISTER_PROLOGUE` or `ZEL_REGISTER_EPILOGUE`; a null `pCallback` clears that slot.
- Like the core registration functions, this can be called only while __hTracer__ is in the disabled state.
- Multiple tracers may register the same function; their callbacks are stacked.
- It requires driver support (see **Driver Support** below) and returns `ZE_RESULT_ERROR_UNSUPPORTED_FEATURE` if the driver does not implement the required hooks.

#### Callback signature

Because an arbitrary extension function has no generated `..params_t` structure, the handler uses the generic signature `zel_pfnDriverExtensionFunctionCb_t` (in `include/loader/ze_loader.h`):

```
void (ZE_APICALL *zel_pfnDriverExtensionFunctionCb_t)(
    void* pParams,                    // driver-defined parameter block (opaque; may be null)
    ze_result_t result,              // epilogue only: the function's return value
    void* pTracerUserData,           // per-tracer user data (from zelTracerCreate)
    void** ppTracerInstanceUserData  // per-call scratch for prologue->epilogue handoff
);
```

`pParams` points to a driver-defined layout for the named function; the driver documents its structure. The remaining parameters follow the same conventions as the core callback handlers described in **Callback Handlers**.

#### When an extension callback fires

A tracer's extension callback for a given (driver, function) fires on a call to that function only when **all** of the following hold:
1. The tracing layer is enabled (see **Enabling Tracing in the Loader**).
2. At least one tracer has registered a callback for that (driver, function), so the loader's wrapper is installed on the driver.
3. That specific tracer is enabled (via __zelTracerSetEnabled__) and registered the callback.

These are the same layered semantics as core-API tracing: the tracing layer is the global switch, and each tracer must also be individually enabled. Registering a callback does not by itself cause it to fire; the tracer must be enabled. Disabling a tracer stops its extension callbacks from firing but leaves the registration in place.

Conditions 1 and 2 together open the driver's extension-tracing gate, and they may be satisfied in either order: as an optimization the loader leaves the gate closed until the first extension callback is registered (so enabling the tracing layer with no extension callbacks costs nothing), then opens it on that first registration. Enabling the layer before or after registering a callback therefore produces the same result.

#### Driver Support

Extension-function tracing requires the driver to implement two hooks, discoverable by name through __zeDriverGetExtensionFunctionAddress__:

- __zelDriverEnableTracing__ — a global gate the loader toggles when the tracing layer is enabled or disabled. While disabled, the driver must not invoke any registered wrapper.
- __zelDriverSetLoaderCallbackForExtension__ — installs (or clears) a single loader-owned prologue/epilogue wrapper for a named extension function. The driver invokes that wrapper around the body of the function.

The loader probes these hooks at driver initialization. Drivers that do not implement them are treated as not supporting extension-function tracing, and __zelTracerDriverExtensionRegisterCallback__ returns `ZE_RESULT_ERROR_UNSUPPORTED_FEATURE`. The corresponding signatures (`zel_pfnDriverEnableTracing_t` and `zel_pfnDriverSetLoaderCallbackForExtension_t`) are defined in `include/loader/ze_loader.h`.

#### Registration lifetime and cleanup on destroy

The loader-owned wrapper installed on the driver for a given (driver, function) is **refcounted separately for the prologue and the epilogue** across all tracers: the prologue wrapper is installed when the first tracer registers a prologue and cleared when the last tracer stops registering one, and the epilogue wrapper likewise. A second tracer registering the same prologue (or epilogue) is idempotent (the wrapper is already installed), and one tracer clearing its slot does not disturb another tracer that still registers the same prologue or epilogue.

__zelTracerDestroy__ releases the destroyed tracer's share of these refcounts automatically. An application does **not** have to clear each extension registration (by re-registering with a null `pCallback`) before destroying a tracer — destroying it decrements every prologue and epilogue it still held, and a driver-side wrapper is uninstalled only when its refcount reaches zero (i.e. no other tracer still registers that prologue or epilogue). This keeps co-registered tracers working and avoids leaving a wrapper installed after its only registrant is gone, which would otherwise force the driver to keep calling into the loader (and the loader to keep threading per-call instance data) for a function no tracer is watching. Destroying a tracer that never registered any extension callback has no effect on any driver wrapper.

Registration state is independent of the enable state: registering installs the driver-side wrapper, and destroying releases it, regardless of whether the tracer or the tracing layer was ever enabled.

## Reset All Callbacks

__zelTracerResetAllCallbacks(zel_tracer_handle_t hTracer)__ can be used to set ALL prologue and epilogue callback handlers to NULL.

## Callback Handlers

Callback handlers are functions that are implemented by the application, and registered through either the set epilogue/set prologue functions, or the RegisterCallback APIs.  The `ze_api.h` header file or the `zel_tracing_register_cb.h` header file contain prototype declarations for these functions. Generally, these functions take the following parameters:

    - __params__ : a structure capturing pointers to the input and output parameters of the current instance.

    - __result__ : the current value of the return value.

    - __pTracerUserData__ : a per-tracer per-API pointer to user's data that is passed into the callback handler functions.

    - __ppTracerInstanceUserData__ : a per-tracer, per-instance, per-thread storage location; typically used for passing data from the prologue to the epilogue. See example below.

##  __zeInit__ is traceable for all calls subsequent from the creation and enabling of the tracer itself.

## Enabling, Disabling and Destruction
The __tracer__ is created in a disabled state and must be explicitly enabled by calling __zelTracerSetEnabled__. The implementation guarantees that __prologue__ and __epilogue__ handlers for a given **L0 API** function will always be executed in pairs; i.e.

- if the __prologue__ function was called and there is a corresponding __epilogue__ function, then the __epilogue__ is guaranteed to be called, even if another thread disabled the __tracer__ between execution

- if the __prologue__ function was not called then the __epilogue__ function is guaranteed not to be called, even if another thread enabled the tracer between execution

The __tracer__ must be disabled by the application before the __tracer__ is destroyed. If multiple threads are in-flight, then callbacks that are in progress for that __tracer__ will continue to execute even after the __tracer__ is disabled; the implementation will stall and wait for any outstanding threads executing a __tracer__ __prologue__ or __epilogue__ functions to complete those during __zelTracerDestroy__ of that __tracer__.

The following pseudo-code demonstrates a basic usage of API tracing:
```
#include "level_zero/ze_api.h"
#include "level_zero/layers/zel_tracing_api.h"
#include "level_zero/loader/ze_loader.h"

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
    my_instance_data_t* instance_data = *(my_instance_data_t**)ppTracerInstanceUserData;

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
    zelTracerCreate(&tracer_desc, &hTracer);

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
    zelTracerCreate(&tracer_desc, &hTracer);

    zelTracerCommandListAppendLaunchKernelRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE, OnEnterCommandListAppendLaunchKernel);
    zelTracerCommandListAppendLaunchKernelRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE, OnExitCommandListAppendLaunchKernel);

    zelTracerSetEnabled(hTracer, true);

    zeCommandListAppendLaunchKernel(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);

    zelTracerSetEnabled(hTracer, false);
    zelTracerDestroy(hTracer);
}

// An example demonstrating dynamic tracing layer control
void DynamicTracingExample( ... )
{
    // Query current tracing layer state
    bool tracingEnabled = false;
    zelGetTracingLayerState(&tracingEnabled);
    printf("Tracing layer initially %s\n", tracingEnabled ? "enabled" : "disabled");

    // Enable the tracing layer dynamically
    ze_result_t result = zelEnableTracingLayer();
    if (result == ZE_RESULT_SUCCESS) {
        printf("Tracing layer enabled successfully\n");
    }

    // Create and configure tracer
    my_tracer_data_t tracer_data = {};
    zel_tracer_desc_t tracer_desc;
    tracer_desc.stype = ZEL_STRUCTURE_TYPE_TRACER_DESC;
    tracer_desc.pUserData = &tracer_data;
    zel_tracer_handle_t hTracer;
    zelTracerCreate(&tracer_desc, &hTracer);

    zelTracerCommandListAppendLaunchKernelRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE, OnEnterCommandListAppendLaunchKernel);
    zelTracerCommandListAppendLaunchKernelRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE, OnExitCommandListAppendLaunchKernel);

    // Enable the tracer (note: tracing layer must also be enabled)
    zelTracerSetEnabled(hTracer, true);

    // Code section where tracing is active
    zeCommandListAppendLaunchKernel(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);

    // Disable the tracer
    zelTracerSetEnabled(hTracer, false);
    zelTracerDestroy(hTracer);

    // Disable the tracing layer to reduce overhead for subsequent code
    zelDisableTracingLayer();

    // Subsequent API calls will not be traced
    zeCommandListAppendLaunchKernel(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);
}

// An example tracing a driver extension function obtained by name
void OnEnterMyExtFunc(
    void* pParams,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData )
{
    // pParams points to the driver-defined parameter block for "zeMyExtFunc".
    printf("entering zeMyExtFunc\n");
}

void ExtensionTracingExample( ze_driver_handle_t hDriver )
{
    my_tracer_data_t tracer_data = {};
    zel_tracer_desc_t tracer_desc;
    tracer_desc.stype = ZEL_STRUCTURE_TYPE_TRACER_DESC;
    tracer_desc.pUserData = &tracer_data;
    zel_tracer_handle_t hTracer;
    zelTracerCreate(&tracer_desc, &hTracer);

    // Register a prologue for an extension function by name (tracer still disabled).
    ze_result_t result = zelTracerDriverExtensionRegisterCallback(
        hTracer, hDriver, "zeMyExtFunc", ZEL_REGISTER_PROLOGUE, OnEnterMyExtFunc);
    if (result == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
        // The driver does not support extension-function tracing.
        zelTracerDestroy(hTracer);
        return;
    }

    // The tracing layer must also be enabled for callbacks to fire.
    zelEnableTracingLayer();
    zelTracerSetEnabled(hTracer, true);

    // Resolve and call the extension function directly; the prologue fires.
    void* pfnRaw = nullptr;
    zeDriverGetExtensionFunctionAddress(hDriver, "zeMyExtFunc", &pfnRaw);
    // ... call the resolved function pointer as documented by the driver ...

    zelTracerSetEnabled(hTracer, false);
    zelTracerDestroy(hTracer);
    zelDisableTracingLayer();
}
```
