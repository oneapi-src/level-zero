# Level Zero Loader APIs

## Introduction
The Level Zero Loader will expose some additional APIs beyond what is defined in the Level Zero spec. The purpose of these APIs will generally be to access and set various loader configuration components.  

This document does not cover APIs specific to individual layers (ie. tracing) or APIs defined in the Level Zero spec.

## API Reference

Exposed Loader APIs will be defined in header files located in this repository at `include/loader`, and installed to `<prefix>/include/level_zero/loader`

###  zelLoaderGetVersions

This API is used to retreive the version information of the loader itself and of any layers that are enabled.

- __*num_elems__  Is a pointer to the number of version components to get. 
- __*versions__   Pointer to address to write version components to. If set to `nullptr`, `num_elems` will be set to the total number of version components available. 

There are currently 3 versioned components assigned the following name strings:
- `"tracing layer"`
- `"validation layer"`
- `"loader"`


### zelLoaderTranslateHandle

When a system has multiple L0 drivers, raw handles returned from the L0 drivers are modified by the loader before being returned to the application.  This allows the loader to determine which handles belong to which driver and forward API calls appropriately.  In most cases the loader will perform this handle translation completely transparently to the application and no manual translation is ever needed.

In some rare cases when the application needs to occasionally bypass the loader, handle conflicts can arise. One such case is when an application wants to call a driver extension function whose address has been retreived with `zeDriverGetExtensionFunctionAddress`

To solve this issue, `zelLoaderTranslateHandle` is used to retrieve the raw driver handle associated with a loader handle.  

- __handleType__  Type of the L0 handle to translate
- __*handleIn__ Input handle to translate
- __**handleOut__ Output location to store the translated handle








