# Level zero loader changelog

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
