# Level Zero Loader APIs

## Introduction
The Level Zero Loader will expose some additional APIs beyond what is defined in the Level Zero spec. The purpose of these APIs will generally be to access and set various loader configuration components.   At the current time, only one such API exists. It's expected more will be added in the future, and they will be documented here.  

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
