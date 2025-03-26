# Level zero loader changelog

## v1.21.7
* Update default SDK install path to include Program Files
## v1.21.6
* Fix to pkgconfig during non build installer cmake install
## v1.21.5
* Check zesInit pfnInit before attempting call
* Added build flag L0_DLL_INTEGRITY_CHECKS to enable integrity check of DLLs
## v1.21.3
* Fix sorting drivers missing function pointers and add multi driver ults
* Add support for SDK installer on windows
## v1.21.2
* Fix driver sorting given driver failures and instrumentation
## v1.21.1
* Fix stype assignment in zello_world
* Given static Loader, allocate lib context_t always as dynamic and enable delayed destroy of context
## v1.21.0
* Add Support for building the L0 Loader statically
## v1.20.6
* Add in missing header for ze_handle_t definition for DDI extension
## v1.20.5
* Add option to enable logging each API call
* basic_leak_checker: add support for zeMemFreeExt
* Fix to teardown check to avoid context use after destroy
## v1.20.4
* Fix stype init for property query during init
* Fix Init error checking to check the validation layer checks
* Extension validation fixed in the parameter validation checker
## v1.20.3
* Implemented basic leak checker in validation layer
* Support for Sorting Drivers based on the devices provided
## v1.20.2
* Fix to Validation Layer Param checking of Extensions for new desc types
## v1.20.1
* Update to spec 1.12.15
* Update Docs for spec links and corrections
## v1.20.0
* Update to spec 1.12
* Allow pkg-config files on Windows as well
* Fix GET_FUNCTION_PTR warnings on windows
* Fix libddi table query code generation
* Fixed pkg-config files generation
* fixed potential memory leaks in events checker
## v1.19.2
* Remove static result in InitDrivers given first init fails
## v1.19.1
* Fix to Use relative paths for events deadlock detection third party headers 
## v1.19.0
* logging full path of loaded library in traces
* Fix utils build
* feature: events deadlock detection in validation layer
* Add Passing in the Result to Validation Checkers at Epilogue
* Disconnect zeInitDrivers and zeDriverGet
* Fix backwards compatibility usage of Get*ProcAddrTable
* Fix to add missing zeKernelGetExp API and header updates
* Fix zeInit Compatibility when zeInitDrivers is undefined
## v1.18.5
* Fix metric types for new experimental types
* Fix/Regenerate the Loader files incorrectly reordered by the scripts.
* Fix ABI checker build/tests
* Update workflows to ABI check with last released tag
## v1.18.4
* Fix Backwards compatibility in ddi structs for EXP features
## v1.18.3
* Update loader headers to spec 1.11 with fixed ddi ordering
* Remove preload of all drivers given zeInitDrivers and update unit tests
## v1.18.2
* Fix code generation of EXP tables and EXP functions to remove invalid new ddi tables and apis.
## v1.18.1
* Fix check for new ddi table in 1.11 and fix space in driver count check.
## v1.18.0
* v1.11 Spec Changes for the L0 Loader
* Wrap linker flags on Windows for IntelLLVM
* Ensure validation_layer::context has init before usage
* Replace exception with error string return in zello_log.h
## v1.17.45
* windows: do not exclude DN_NEED_RESTART drivers if LevelZeroStagedDriverPath is set
## v1.17.44
* Add missing guard around debug message
## v1.17.43
* Switch to monotonically increasing patch numbers
* Fix warning by updating min cmake version to 3.5
* Add missing guards around debug messages
## v1.17.42
* Fix SysMan driver pointers given no sysman env and no zesInit (#193)
* Prevent reinit when zes/ze handles have already been retrieved (#192)
## v1.17.39
* Add Ubuntu 24.04 and 24.10 builds
* Proper installation rules
* Enable testing with ctest
* Fix reading updated state of the driver_t for checking initStatus (#188)
* Avoid DDI table reinit if ZE_ENABLE_LOADER_INTERCEPT=1 (#187)
* Update spdlog headers (#186)
* Fix handle translation when ddi table fallback (#185)
* Split Ze and Zes Drivers and only release drivers at close (#184)
* Fix issues with intercept layer and zesInit/zeInit given fallback to passthrough (#183)
* Fix global teardown of loader handles and check driver status in init_driver (#182)
## v1.17.28
* Add GPU-legacy1 driver to list of known names on Linux
* Fix first zeinit to allow for layer checks
## v1.17.25
* Don't exchange zet/zes DDI tables for tracing
* Fix OpenSSF token permissions warning
* Rename init functions to avoid confusion with zeInit
* Add missing ZE_RESULT_ERROR_UNINITIALIZED checks to zesDriverGet
## v1.17.19
* Fix DriverGet to handle failed drivers and avoid layer init during checks
## v1.17.17
* Fix layer init with multiple drivers and ensure init for instrumentation support
* Change loader log file location
* Add update-spec.yml workflow
* Define FMT_HEADER_ONLY for spdlog inclusion
* spdlog: Use system library if requested
* Create scorecard.yml
* Support for Pluggable Validation Layer Checkers
* Add NPU Driver to list of known names on linux
* Correct casting in tracing layer sample code
## v1.17.6
* Bundle spdlog headers as part of build vs library build
## v1.17.2
* Recognize mutable command list struct types in validation layer
## v1.17.0
* Update to support v1.9.3 of the L0 Spec
## v1.16.15
* Fix Tracing Layer Dynamic Enable Counter
## v1.16.14
* Fix loading environment strings
* Avoid init of Logger unless Enabled by ZEL_ENABLE_LOADER_LOGGING
## v1.16.11
* fix Logging build to be static linked
## v1.16.9
* Fix code Gen scripts for zesInit Only
* Fix Build using IntelLLVM compiler
* Installation path fixes
* Add USE_ASAN cmake flag for address sanitization
## v1.16.1
* Fix to spec generated api version defines
## v1.16.0
* Update to spec 1.9.1
## v1.15.13
* Enable for zesInit to run with zeInit without duplicate init
* Addressed OpenSSF Token Permissions
* Fix for missing extension types in the validation layer
* Added structure for Loader validation testing
## v1.15.8
* Fix build when using clang-cl on Windows
* set RUNTIME DESTINATION in install for layer libraries
* added github actions runs on latest windows
* Windows.h replaced with windows.h
* Added support for enabling/disabling tracing layer during runtime
* check in DriverGet to verify the dditable pointer is valid
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
