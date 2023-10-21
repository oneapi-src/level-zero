# Level zero loader changelog

## v1.15.1
* Fix Windows build for Control Flow Guard Mitigation.
## v1.15.0
* Update to spec 1.8.0
## v1.14.0
* Update to spec 1.7.8
* Fix intercept layer access to array of handles and return of logs
* Enable All warnings and warnings as errors to cleanup code
* Add validation of module extended descriptor
* Add ZE_ENABLE_LOADER_DEBUG_TRACE for tracking Library Load/Unload errors
## v1.13.5
* Updated code generating scripts for updated spec and init functionality
* Change zeInit to only init on the first call in a process
## v1.13.1
* Fix Formatting issues
## v1.13.0
* Update to spec 1.7.0
* Add reference to Tracing Layer in README.md
* Update dll copyright
## v1.12.0
* Update to spec 1.6.10
## v1.11.0
* Update to spec 1.6.3
* Add validation for handle lifetime
* Improve driver teardown handling

## v1.10.0
* Update to spec 1.6
* Added validation for stype and pnext


## v1.9.9
* Update to spec 1.5.17
* Fix for calling zeInit in zesInit path
* Added readme for validation layer
* Refactor of validation layer to prepare for future enhancements
* Updated Contributing Document with more guidance

## v1.9.4
* Add support for Level Zero spec v1.5
* Fix some compilation issues with windows non-vc compiler
* Fix building when included in another cmake project. 

## v1.8.12
* Add Image View Handle to image map for SetArgument for translating image handles for multi drivers
* Support for translating images/samplers for multi drivers

## v1.8.8
* Update Extension and Experimental Features to return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE instead of ZE_RESULT_ERROR_UNINITIALIZED when not found.

## v1.8.5
* Remove RTLD_DEEPBIND from driver dlopen calls
* Add loader code generation scripts 
* Update to spec 1.4.8 which includes fixes to zes_power_limit_ext_desc_t

## v1.8.1 
* Add missing sTypes
* Fix argument names in some exp APIs

## v1.8.0
* Add Support for L0 Spec v1.4 which includes
  * Core Fabric Topology API
  * Core Extension for memory BW
  * Core Extension for LUID query
  * Sysman ECC 
  * Sysman Power Limits Extension

   
## v1.7.15
* Fix bug during multiple calls to zeInit with no driver present
* Add option to support build with sccache

## v1.7.9
* Fix bug in loader handle translation API
* Fix tracing layer functionality in newer APIs

## v1.7.4
* Addition of new Loader API to perform handle translations. See doc/loader_api.md
* Add Ability to read optional Level Zero Registry Key Containing the Level Zero Loader libraries on windows
* Update L0 headers to 1.3.7 Spec which includes:
  * Fix to bool type that caused compilation issues
  * Addition of new metrics enum for stall sampling
  * Changing some param names for consistency

## v1.6.2
* Removed Null Driver Tracing Support (Tracing supported using the Layer implementation)
* Fixed ze_callbacks_t for backwards compatibility
## v1.6.1
* Updated L0 API headers to 1.3.0 which includes:
  * Get PCI Properties Extension
  * Get Image Allocation Properties Extension
  * Memory Free Extension
  * Module Linkage Inspection Extension
  * Image Copy To/From Memory Extensions
  * GDDR Memory Type support in SysMan
  * PCIe Card-level power domains in SysMan
* Fixed Return Codes for uninitialized function pointers & tables to return ZE_RESULT_ERROR_UNINITIALIZED vs ZE_RESULT_ERROR_UNSUPPORTED_VERSION
* Tracing Context handled during library init & destroy
* Enable CPACK support for ARM64 Package Generation

## v1.5.4
* Fixed a bug verifying L0 Driver stability after initializing ddi tables
* Updated Windows usage of LoadLibrary for security to only load libraries from system32
* Fixed a bug allowing nullptr keys into handle maps

## v1.5.0
* Added Intel VPU driver to Linux known driver list
* Fixed default symbol visibility in Linux builds
* Added zeInit call earlier in loader init path to prevent loading drivers that don't match the ze_init_flags_t
* Fixed build for certain SLES distros
* Fixed bug that prevented tracers from being reenabled after being disabled. 
* Multi Driver Support: Return success if initialization of at least one driver succeeds. 
* Updated L0 API headers to 1.2.43 which includes:
  * Clarification to documentation of several APIs
  * Added missing STYPE ZE_STRUCTURE_TYPE_IMAGE_MEMORY_EXP_PROPERTIES
  * Added new experimental metrics extension to retrieve multiple metrics values

## v1.4.1
* Added support for Level Zero Specification 1.2.13
* Fixed a bug that resulted in zeInit failing when multiple drivers are discovered and one of them fails to load. 

## v1.3.7
* Fixed build warnings generated when `-Wall` is enabled

## v1.3.6
* New Tracing Layer APIs to support tracing Level Zero core APIs introduced after the 1.0 Specification. A change of design was needed to allow extension to new APIs without breaking backwards compatibility of original tracing APIs. The original tracing layer APIs will continue to be supported for 1.0 core APIs, but users are encouraged to switch to the new tracing layer APIs. 
* New Loader API to retrieve version information of loader and layers: `zelLoaderGetVersions`
* Enabled discovery of Level Zero Compute Accelerators Drivers on windows
* Bug Fixes:
  * Fixed loader bug that could cause corruption of handles when there are multiple drivers loaded. 
  * Corrected version check in layers to future-proof compatibility checks


## v1.2.3
* Support for the new 1.1 Level Zero Specification
* Improved library variable lifetime management by initializing variables at load time rather than as static globals. 
* Added environment variable that allows optionally specifying runtime drivers to use on Linux
* Note: Tracing Layer support is not yet available for the APIs newly introduced in the 1.1 spec. Tracing layer support for all other APIs remains functional. 



## v1.1.0
Note: Level Zero Specification API did not change.

* Update loader library to 1.1.0 to indicate addition of tracing layer implementation and associated APIs
* Fixed bug when reading windows environment variables set by process before zeInit call. Before variables were not read correctly resulting in layers not being enabled as expected
* Fixed bug in loader when using multiple drivers and a driver API returns an error code. Previously loader would incorrectly translate output handles from failed API calls
* Deprecated a tracing implementation layer descriptor enum value due to incorrect name and added a replacement.
