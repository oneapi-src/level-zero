# Certification Checker

## Description
The Certification Checker is a validation layer component designed to ensure that API usage conforms to a specific version supported by the driver.
Its primary function is to restrict the use of APIs to those that are available in the version reported by the driver or a version explicitly specified by the user.
If an attempt is made to use an API introduced in a later version, the checker shall return `ZE_RESULT_ERROR_UNSUPPORTED_VERSION`.

When enabled, the checker intercepts API calls and compares the version of each API used against the version supported by the driver.
There are two modes:
- **Default:**
  The supported version is, by default, set to the loader's defined `ZE_API_VERSION_CURRENT`.
  It is updated to the driver’s reported version once `zeDriverGetApiVersion` is first called.
- **Explicit:**
  The version can be overridden by setting the `ZEL_CERTIFICATION_CHECKER_VERSION` environment variable to a value of `<major>.<minor>`. Once set, the version returned by `zeDriverGetApiVersion` is ignored.
  For example, to restrict API usage to version 1.6:
  `export ZEL_CERTIFICATION_CHECKER_VERSION=1.6`