/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// Unit tests for the loader's Driver DDI Handles extension detection performed
// during context_t::driverSorting().
//
// These tests exercise both:
//   * the legacy path  - a driver advertises the Driver DDI Handles extension
//                         via zeDriverGetExtensionProperties and the loader
//                         honors the reported extension version (>= 1.1 required).
//   * the new path      - a driver reporting API version >= 1.17 is assumed to
//                         support the Driver DDI Handles extension at version 1.1
//                         without any extension-property query (the "implied"
//                         superset behavior).

#include "gtest/gtest.h"

#include "source/loader/ze_loader_internal.h"
#include "ze_api.h"

#include <cstring>

namespace {

// Captureless lambdas are used for the mock dditable, so the configuration and
// the call counters live in process-global state.
struct MockDriverControl {
    // Reported by zeDriverGetApiVersion.
    ze_api_version_t apiVersion = ZE_API_VERSION_CURRENT;
    // When false, the driver does not expose pfnGetApiVersion at all.
    bool provideApiVersion = true;

    // Controls what zeDriverGetExtensionProperties advertises.
    bool reportDdiHandlesExt = true;
    ze_driver_ddi_handles_ext_version_t ddiExtVersion = ZE_DRIVER_DDI_HANDLES_EXT_VERSION_1_1;

    // Controls whether zeDriverGetProperties sets the DDI handle supported flag.
    bool reportDdiSupportedFlag = true;

    // Call counters used to prove which queries the loader actually performed.
    int apiVersionCalls = 0;
    int extPropCalls = 0;
    int getPropertiesCalls = 0;
};

static MockDriverControl g_mock;

// Sentinel handles returned by the mock driver/device enumeration.
ze_driver_handle_t mockDriverHandle() {
    return reinterpret_cast<ze_driver_handle_t>(0x1234);
}
ze_device_handle_t mockDeviceHandle() {
    return reinterpret_cast<ze_device_handle_t>(0x5678);
}

// Build a driver_t whose dditable is wired to the mock implementation above.
loader::driver_t makeMockDriver() {
    loader::driver_t driver;
    driver.name = "mock_ddi_driver";
    driver.initStatus = ZE_RESULT_SUCCESS;
    driver.legacyInitAttempted = true;
    driver.zerddiInitResult = ZE_RESULT_SUCCESS; // so zerDriverHandle is populated
    driver.driverDDIHandleSupportQueried = false;
    driver.zerDriverDDISupported = true;          // matches the runtime default
    driver.zerDriverHandle = nullptr;
    driver.driverType = loader::ZEL_DRIVER_TYPE_DISCRETE_GPU;

    driver.dditable.ze.Driver.pfnGet = [](uint32_t *pCount, ze_driver_handle_t *phDrivers) -> ze_result_t {
        *pCount = 1;
        if (phDrivers != nullptr) {
            phDrivers[0] = mockDriverHandle();
        }
        return ZE_RESULT_SUCCESS;
    };

    if (g_mock.provideApiVersion) {
        driver.dditable.ze.Driver.pfnGetApiVersion = [](ze_driver_handle_t, ze_api_version_t *version) -> ze_result_t {
            g_mock.apiVersionCalls++;
            *version = g_mock.apiVersion;
            return ZE_RESULT_SUCCESS;
        };
    }

    driver.dditable.ze.Driver.pfnGetExtensionProperties =
        [](ze_driver_handle_t, uint32_t *pCount, ze_driver_extension_properties_t *pExtensionProperties) -> ze_result_t {
        g_mock.extPropCalls++;
        const uint32_t available = g_mock.reportDdiHandlesExt ? 1u : 0u;
        if (pExtensionProperties == nullptr) {
            *pCount = available;
            return ZE_RESULT_SUCCESS;
        }
        if (g_mock.reportDdiHandlesExt && *pCount >= 1) {
            ze_driver_extension_properties_t ext = {};
#if defined(_WIN32)
            strcpy_s(ext.name, ZE_DRIVER_DDI_HANDLES_EXT_NAME);
#else
            std::strcpy(ext.name, ZE_DRIVER_DDI_HANDLES_EXT_NAME);
#endif
            ext.version = g_mock.ddiExtVersion;
            pExtensionProperties[0] = ext;
        }
        *pCount = available;
        return ZE_RESULT_SUCCESS;
    };

    driver.dditable.ze.Driver.pfnGetProperties = [](ze_driver_handle_t, ze_driver_properties_t *pDriverProperties) -> ze_result_t {
        g_mock.getPropertiesCalls++;
        auto pNext = reinterpret_cast<ze_base_properties_t *>(pDriverProperties->pNext);
        while (pNext != nullptr) {
            if (pNext->stype == ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES && g_mock.reportDdiSupportedFlag) {
                auto pDdi = reinterpret_cast<ze_driver_ddi_handles_ext_properties_t *>(pNext);
                pDdi->flags = ZE_DRIVER_DDI_HANDLE_EXT_FLAG_DDI_HANDLE_EXT_SUPPORTED;
            }
            pNext = reinterpret_cast<ze_base_properties_t *>(pNext->pNext);
        }
        return ZE_RESULT_SUCCESS;
    };

    driver.dditable.ze.Device.pfnGet = [](ze_driver_handle_t, uint32_t *pCount, ze_device_handle_t *phDevices) -> ze_result_t {
        *pCount = 1;
        if (phDevices != nullptr) {
            phDevices[0] = mockDeviceHandle();
        }
        return ZE_RESULT_SUCCESS;
    };

    driver.dditable.ze.Device.pfnGetProperties = [](ze_device_handle_t, ze_device_properties_t *pDeviceProperties) -> ze_result_t {
        pDeviceProperties->type = ZE_DEVICE_TYPE_GPU;
        pDeviceProperties->flags = 0; // discrete GPU
        return ZE_RESULT_SUCCESS;
    };

    return driver;
}

class DdiDriverPathUnitTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear ZEL_DRIVERS_ORDER so driverOrdering() does not reshuffle the vector.
        // putenv_safe is provided as a macro by ze_util.h.
        putenv_safe(const_cast<char *>("ZEL_DRIVERS_ORDER="));

        if (!loader::context) {
            loader::context = new loader::context_t();
        }
        loader::context->debugTraceEnabled = false;

        g_mock = MockDriverControl{};
    }

    // Run driverSorting() over a single mock driver and return it back for inspection.
    loader::driver_t sortSingleDriver() {
        loader::driver_vector_t drivers;
        drivers.push_back(makeMockDriver());
        // desc == nullptr forces the zeDriverGet path (no zeInitDrivers).
        EXPECT_TRUE(loader::context->driverSorting(&drivers, nullptr, false));
        EXPECT_EQ(1u, drivers.size());
        return drivers.front();
    }
};

// ---------------------------------------------------------------------------
// Legacy behavior: extension-property based detection (API version < 1.17)
// ---------------------------------------------------------------------------

// A pre-1.17 driver that advertises DDI Handles Ext v1.1 and reports the
// supported flag is treated as DDI-capable.
TEST_F(DdiDriverPathUnitTest, LegacyDriverWithExtV1_1AndSupportedFlagIsDDISupported) {
    g_mock.apiVersion = ZE_API_VERSION_1_16; // pre-1.17 forces the legacy extension-property path
    g_mock.reportDdiHandlesExt = true;
    g_mock.ddiExtVersion = ZE_DRIVER_DDI_HANDLES_EXT_VERSION_1_1;
    g_mock.reportDdiSupportedFlag = true;

    auto driver = sortSingleDriver();

    EXPECT_TRUE(driver.zerDriverDDISupported);
    EXPECT_EQ(mockDriverHandle(), driver.zerDriverHandle);
    EXPECT_TRUE(driver.driverDDIHandleSupportQueried);
    EXPECT_TRUE(driver.properties.flags & ZE_DRIVER_DDI_HANDLE_EXT_FLAG_DDI_HANDLE_EXT_SUPPORTED);

    // The legacy path must query the extension list and the driver properties.
    EXPECT_GT(g_mock.extPropCalls, 0);
    EXPECT_GT(g_mock.getPropertiesCalls, 0);
}

// A pre-1.17 driver that advertises only DDI Handles Ext v1.0 does not meet the
// minimum version for the ZER (runtime) APIs, so DDI support is disabled.
TEST_F(DdiDriverPathUnitTest, LegacyDriverWithExtV1_0IsNotDDISupported) {
    g_mock.apiVersion = ZE_API_VERSION_1_16; // pre-1.17 forces the legacy extension-property path
    g_mock.reportDdiHandlesExt = true;
    g_mock.ddiExtVersion = ZE_DRIVER_DDI_HANDLES_EXT_VERSION_1_0;
    g_mock.reportDdiSupportedFlag = true;

    auto driver = sortSingleDriver();

    EXPECT_FALSE(driver.zerDriverDDISupported);
    EXPECT_EQ(nullptr, driver.zerDriverHandle);

    // Legacy detection still queries the extension list.
    EXPECT_GT(g_mock.extPropCalls, 0);
}

// A driver that exposes no API-version entry point falls back to the legacy
// extension-property detection even though we cannot read its API version.
TEST_F(DdiDriverPathUnitTest, DriverWithoutApiVersionEntryPointUsesLegacyPath) {
    g_mock.provideApiVersion = false;
    g_mock.reportDdiHandlesExt = true;
    g_mock.ddiExtVersion = ZE_DRIVER_DDI_HANDLES_EXT_VERSION_1_1;
    g_mock.reportDdiSupportedFlag = true;

    auto driver = sortSingleDriver();

    EXPECT_TRUE(driver.zerDriverDDISupported);
    EXPECT_TRUE(driver.properties.flags & ZE_DRIVER_DDI_HANDLE_EXT_FLAG_DDI_HANDLE_EXT_SUPPORTED);
    EXPECT_EQ(0, g_mock.apiVersionCalls);
    EXPECT_GT(g_mock.extPropCalls, 0);
}

// ---------------------------------------------------------------------------
// New behavior: API version >= 1.17 implies DDI Handles Ext v1.1 support
// ---------------------------------------------------------------------------

// A 1.17 driver is assumed DDI-capable even when its extension list reports the
// old v1.0 version - the extension/property queries must be skipped entirely.
TEST_F(DdiDriverPathUnitTest, Driver1_17ImpliesDDISupportWithoutExtensionQuery) {
    g_mock.apiVersion = static_cast<ze_api_version_t>(ZE_MAKE_VERSION(1, 17));
    g_mock.reportDdiHandlesExt = true;
    g_mock.ddiExtVersion = ZE_DRIVER_DDI_HANDLES_EXT_VERSION_1_0; // would fail legacy check
    g_mock.reportDdiSupportedFlag = false;                       // properties wouldn't report support

    auto driver = sortSingleDriver();

    EXPECT_TRUE(driver.zerDriverDDISupported);
    EXPECT_EQ(mockDriverHandle(), driver.zerDriverHandle);
    EXPECT_TRUE(driver.driverDDIHandleSupportQueried);
    EXPECT_TRUE(driver.properties.flags & ZE_DRIVER_DDI_HANDLE_EXT_FLAG_DDI_HANDLE_EXT_SUPPORTED);

    // The whole point of the new path: no extension property check is needed.
    EXPECT_EQ(1, g_mock.apiVersionCalls);
    EXPECT_EQ(0, g_mock.extPropCalls);
    EXPECT_EQ(0, g_mock.getPropertiesCalls);
}

// A 1.17 driver that does not advertise the DDI Handles extension at all is
// still treated as supported (superset), again without any extension query.
TEST_F(DdiDriverPathUnitTest, Driver1_17ImpliesDDISupportWhenExtensionAbsent) {
    g_mock.apiVersion = static_cast<ze_api_version_t>(ZE_MAKE_VERSION(1, 17));
    g_mock.reportDdiHandlesExt = false;
    g_mock.reportDdiSupportedFlag = false;

    auto driver = sortSingleDriver();

    EXPECT_TRUE(driver.zerDriverDDISupported);
    EXPECT_EQ(mockDriverHandle(), driver.zerDriverHandle);
    EXPECT_TRUE(driver.properties.flags & ZE_DRIVER_DDI_HANDLE_EXT_FLAG_DDI_HANDLE_EXT_SUPPORTED);
    EXPECT_EQ(0, g_mock.extPropCalls);
    EXPECT_EQ(0, g_mock.getPropertiesCalls);
}

// A newer-than-1.17 driver is also covered by the >= comparison.
TEST_F(DdiDriverPathUnitTest, DriverNewerThan1_17ImpliesDDISupport) {
    g_mock.apiVersion = static_cast<ze_api_version_t>(ZE_MAKE_VERSION(1, 99));
    g_mock.reportDdiHandlesExt = false;
    g_mock.reportDdiSupportedFlag = false;

    auto driver = sortSingleDriver();

    EXPECT_TRUE(driver.zerDriverDDISupported);
    EXPECT_TRUE(driver.properties.flags & ZE_DRIVER_DDI_HANDLE_EXT_FLAG_DDI_HANDLE_EXT_SUPPORTED);
    EXPECT_EQ(0, g_mock.extPropCalls);
}

// Boundary check: API version 1.16 must NOT take the implied path - it has to
// fall back to the extension-property detection.
TEST_F(DdiDriverPathUnitTest, Driver1_16DoesNotTakeImpliedPath) {
    g_mock.apiVersion = static_cast<ze_api_version_t>(ZE_MAKE_VERSION(1, 16));
    g_mock.reportDdiHandlesExt = true;
    g_mock.ddiExtVersion = ZE_DRIVER_DDI_HANDLES_EXT_VERSION_1_0; // legacy check should reject
    g_mock.reportDdiSupportedFlag = true;

    auto driver = sortSingleDriver();

    // Because 1.16 uses the legacy path and the ext reports v1.0, DDI is disabled.
    EXPECT_FALSE(driver.zerDriverDDISupported);
    EXPECT_EQ(nullptr, driver.zerDriverHandle);
    EXPECT_GT(g_mock.extPropCalls, 0);
}

} // namespace
