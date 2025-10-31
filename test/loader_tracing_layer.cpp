/*
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"

#include "loader/ze_loader.h"
#include "ze_api.h"
#include "zer_api.h"
#include "layers/zel_tracing_register_cb.h"
#include "layers/zel_tracing_api.h"

#include <vector>
#include <map>
#include <algorithm>

#if defined(_WIN32)
#include <windows.h>
#define putenv_safe _putenv
#else
#include <cstdlib>
#define putenv_safe putenv
#endif

namespace
{

    inline std::string getenv_string(const char *name)
    {

        const char *env = nullptr;
#if defined(_WIN32)
        char buffer[1024];
        auto rc = GetEnvironmentVariable(name, buffer, 1024);
        if (0 != rc && rc <= 1024)
        {
            env = buffer;
        }
#else
        env = getenv(name);
#endif

        if (nullptr != env)
        {
            return std::string(env);
        }
        else
        {
            return std::string("");
        }
    }

    inline bool compare_env(const char *name, const char *expected_value)
    {
        std::string env_value = getenv_string(name);
        return env_value == expected_value;
    }

    class TracingTest : public ::testing::Test
    {
    public:
        enum class InitMethod
        {
            ZEINIT,
            ZEINIT_DRIVERS
        };

        enum class TracingMode
        {
            STATIC_TRACING,
            DYNAMIC_TRACING
        };

        enum class CallbackType
        {
            PROLOGUE_ONLY,
            EPILOGUE_ONLY,
            PROLOGUE_AND_EPILOGUE
        };

    protected:
        struct TracingData
        {
            std::map<std::string, uint32_t> zerPrologueCallCounts;
            std::map<std::string, uint32_t> zerEpilogueCallCounts;

            std::map<std::string, uint32_t> zePrologueCallCounts;
            std::map<std::string, uint32_t> zeEpilogueCallCounts;

            bool dynamicTracingEnabled = false;

            void reset()
            {
                zerPrologueCallCounts.clear();
                zerEpilogueCallCounts.clear();
                zePrologueCallCounts.clear();
                zeEpilogueCallCounts.clear();
                dynamicTracingEnabled = false;
            }

            // ZER API methods
            void incrementZerPrologueCallCount(const std::string &apiName)
            {
                zerPrologueCallCounts[apiName]++;
            }

            void incrementZerEpilogueCallCount(const std::string &apiName)
            {
                zerEpilogueCallCounts[apiName]++;
            }

            uint32_t getZerPrologueCallCount(const std::string &apiName) const
            {
                auto it = zerPrologueCallCounts.find(apiName);
                return (it != zerPrologueCallCounts.end()) ? it->second : 0;
            }

            uint32_t getZerEpilogueCallCount(const std::string &apiName) const
            {
                auto it = zerEpilogueCallCounts.find(apiName);
                return (it != zerEpilogueCallCounts.end()) ? it->second : 0;
            }

            // ZE API methods
            void incrementZePrologueCallCount(const std::string &apiName)
            {
                zePrologueCallCounts[apiName]++;
            }

            void incrementZeEpilogueCallCount(const std::string &apiName)
            {
                zeEpilogueCallCounts[apiName]++;
            }

            uint32_t getZePrologueCallCount(const std::string &apiName) const
            {
                auto it = zePrologueCallCounts.find(apiName);
                return (it != zePrologueCallCounts.end()) ? it->second : 0;
            }

            uint32_t getZeEpilogueCallCount(const std::string &apiName) const
            {
                auto it = zeEpilogueCallCounts.find(apiName);
                return (it != zeEpilogueCallCounts.end()) ? it->second : 0;
            }
        };

        TracingData tracingData;

        void SetUp() override
        {
            putenv_safe(const_cast<char *>("ZE_ENABLE_LOADER_INTERCEPT=1"));
            putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0"));

            tracingData.reset();
        }

        void TearDown() override
        {
            if (tracingData.dynamicTracingEnabled)
            {
                zelDisableTracingLayer();
                tracingData.dynamicTracingEnabled = false;
            }

            putenv_safe(const_cast<char *>("ZE_ENABLE_TRACING_LAYER="));
            putenv_safe(const_cast<char *>("ZE_ENABLE_LOADER_INTERCEPT="));
            putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT="));
        }

        void initializeLevelZero(InitMethod method, std::vector<ze_driver_handle_t> &drivers)
        {
            if (method == InitMethod::ZEINIT)
            {
                uint32_t driverGetCount = 0;
                EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
                EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverGetCount, nullptr));
                EXPECT_GT(driverGetCount, 0);
                drivers.resize(driverGetCount);
                EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverGetCount, drivers.data()));
            }
            else if (method == InitMethod::ZEINIT_DRIVERS)
            {
                uint32_t pInitDriversCount = 0;
                ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
                desc.flags = UINT32_MAX;
                desc.pNext = nullptr;
                EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
                drivers.resize(pInitDriversCount);
                EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
                EXPECT_GT(pInitDriversCount, 0);
            }
        }

        void setupTracing(TracingMode mode)
        {
            if (mode == TracingMode::STATIC_TRACING)
            {
                putenv_safe(const_cast<char *>("ZE_ENABLE_TRACING_LAYER=1"));
            }
        }

        ze_result_t enableDynamicTracing()
        {
            ze_result_t result = zelEnableTracingLayer();
            if (result == ZE_RESULT_SUCCESS)
            {
                tracingData.dynamicTracingEnabled = true;
            }
            return result;
        }

        ze_result_t disableDynamicTracing()
        {
            ze_result_t result = zelDisableTracingLayer();
            if (result == ZE_RESULT_SUCCESS)
            {
                tracingData.dynamicTracingEnabled = false;
            }
            return result;
        }

        zel_tracer_handle_t createTracer()
        {
            zel_tracer_handle_t hTracer = nullptr;
            zel_tracer_desc_t tracerDesc = {};
            tracerDesc.stype = ZEL_STRUCTURE_TYPE_TRACER_DESC;
            tracerDesc.pUserData = &tracingData;
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerCreate(&tracerDesc, &hTracer));
            return hTracer;
        }

        void destroyTracer(zel_tracer_handle_t hTracer)
        {
            if (hTracer != nullptr)
            {
                zelTracerSetEnabled(hTracer, false);
                zelTracerDestroy(hTracer);
            }
        }

        void registerZerPrologueCallbacks(zel_tracer_handle_t hTracer)
        {
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerGetLastErrorDescriptionRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                          +TracingTest::zerGetLastErrorDescriptionPrologueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerTranslateDeviceHandleToIdentifierRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                                    +TracingTest::zerTranslateDeviceHandleToIdentifierPrologueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerTranslateIdentifierToDeviceHandleRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                                    +TracingTest::zerTranslateIdentifierToDeviceHandlePrologueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerGetDefaultContextRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                    +TracingTest::zerGetDefaultContextPrologueCallback));
        }

        void registerZerEpilogueCallbacks(zel_tracer_handle_t hTracer)
        {
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerGetLastErrorDescriptionRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                          +TracingTest::zerGetLastErrorDescriptionEpilogueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerTranslateDeviceHandleToIdentifierRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                                    +TracingTest::zerTranslateDeviceHandleToIdentifierEpilogueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerTranslateIdentifierToDeviceHandleRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                                    +TracingTest::zerTranslateIdentifierToDeviceHandleEpilogueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerGetDefaultContextRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                    +TracingTest::zerGetDefaultContextEpilogueCallback));
        }

        void registerZePrologueCallbacks(zel_tracer_handle_t hTracer)
        {
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerDeviceGetCommandQueueGroupPropertiesRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                                       +TracingTest::zeDeviceGetCommandQueueGroupPropertiesPrologueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerDeviceGetMemoryPropertiesRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                            +TracingTest::zeDeviceGetMemoryPropertiesPrologueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerDeviceGetMemoryAccessPropertiesRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                                  +TracingTest::zeDeviceGetMemoryAccessPropertiesPrologueCallback));
        }

        void registerZeEpilogueCallbacks(zel_tracer_handle_t hTracer)
        {
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerDeviceGetCommandQueueGroupPropertiesRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                                       +TracingTest::zeDeviceGetCommandQueueGroupPropertiesEpilogueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerDeviceGetMemoryPropertiesRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                            +TracingTest::zeDeviceGetMemoryPropertiesEpilogueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerDeviceGetMemoryAccessPropertiesRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                                  +TracingTest::zeDeviceGetMemoryAccessPropertiesEpilogueCallback));
        }

        void callAllZerApis()
        {
            const char *errorString = nullptr;
            uint32_t deviceId = 0;
            ze_device_handle_t translatedDevice = nullptr;
            ze_context_handle_t defaultContext = nullptr;

            ze_result_t result = zerGetLastErrorDescription(&errorString);
            EXPECT_EQ(ZE_RESULT_SUCCESS, result);
            EXPECT_TRUE(compare_env("zerGetLastErrorDescription", "1"));

            deviceId = zerTranslateDeviceHandleToIdentifier(nullptr);
            (void)deviceId;
            EXPECT_TRUE(compare_env("zerTranslateDeviceHandleToIdentifier", "1"));

            translatedDevice = zerTranslateIdentifierToDeviceHandle(deviceId);
            (void)translatedDevice;
            EXPECT_TRUE(compare_env("zerTranslateIdentifierToDeviceHandle", "1"));

            defaultContext = zerGetDefaultContext();
            (void)defaultContext;
            EXPECT_TRUE(compare_env("zerGetDefaultContext", "1"));
        }

        void callBasicZeApis(std::vector<ze_driver_handle_t> &drivers)
        {
            uint32_t deviceCount = 1;
            ze_result_t result{};

            std::vector<ze_device_handle_t> devices(deviceCount);
            result = zeDeviceGet(drivers[0], &deviceCount, devices.data());
            EXPECT_GT(deviceCount, 0);
            EXPECT_EQ(ZE_RESULT_SUCCESS, result);

            uint32_t queueGroupCount = 0;
            result = zeDeviceGetCommandQueueGroupProperties(devices[0], &queueGroupCount, nullptr);
            EXPECT_EQ(ZE_RESULT_SUCCESS, result);
            EXPECT_TRUE(compare_env("zeDeviceGetCommandQueueGroupProperties", "1"));

            uint32_t memoryCount = 0;
            result = zeDeviceGetMemoryProperties(devices[0], &memoryCount, nullptr);
            EXPECT_EQ(ZE_RESULT_SUCCESS, result);
            EXPECT_TRUE(compare_env("zeDeviceGetMemoryProperties", "1"));

            ze_device_memory_access_properties_t memoryAccessProperties = {};
            memoryAccessProperties.stype = ZE_STRUCTURE_TYPE_DEVICE_MEMORY_ACCESS_PROPERTIES;
            result = zeDeviceGetMemoryAccessProperties(devices[0], &memoryAccessProperties);
            EXPECT_EQ(ZE_RESULT_SUCCESS, result);
            EXPECT_TRUE(compare_env("zeDeviceGetMemoryAccessProperties", "1"));
        }

        void verifyZerCallbackCounts(const std::map<std::string, uint32_t> &expectedCounts, CallbackType stage)
        {
            for (const auto &expected : expectedCounts)
            {
                if (stage == CallbackType::PROLOGUE_ONLY || stage == CallbackType::PROLOGUE_AND_EPILOGUE)
                {
                    uint32_t actualCount = tracingData.getZerPrologueCallCount(expected.first);
                    EXPECT_EQ(expected.second, actualCount);
                }

                if (stage == CallbackType::EPILOGUE_ONLY || stage == CallbackType::PROLOGUE_AND_EPILOGUE)
                {
                    uint32_t actualCount = tracingData.getZerEpilogueCallCount(expected.first);
                    EXPECT_EQ(expected.second, actualCount);
                }
            }
        }

        void verifyAllZerApisCalled(uint32_t expectedCount, CallbackType stage)
        {
            std::map<std::string, uint32_t> expectedCounts = {
                {"zerGetLastErrorDescription", expectedCount},
                {"zerTranslateDeviceHandleToIdentifier", expectedCount},
                {"zerTranslateIdentifierToDeviceHandle", expectedCount},
                {"zerGetDefaultContext", expectedCount}};
            verifyZerCallbackCounts(expectedCounts, stage);
        }

        void verifyAllZerApisCalledBothCallbackTypes(uint32_t expectedCount)
        {
            verifyAllZerApisCalled(expectedCount, CallbackType::PROLOGUE_AND_EPILOGUE);
        }

        void verifyZeCallbackCounts(const std::map<std::string, uint32_t> &expectedCounts, CallbackType stage)
        {
            for (const auto &expected : expectedCounts)
            {
                if (stage == CallbackType::PROLOGUE_ONLY || stage == CallbackType::PROLOGUE_AND_EPILOGUE)
                {
                    uint32_t actualCount = tracingData.getZePrologueCallCount(expected.first);
                    EXPECT_EQ(expected.second, actualCount);
                }

                if (stage == CallbackType::EPILOGUE_ONLY || stage == CallbackType::PROLOGUE_AND_EPILOGUE)
                {
                    uint32_t actualCount = tracingData.getZeEpilogueCallCount(expected.first);
                    EXPECT_EQ(expected.second, actualCount);
                }
            }
        }

        void verifyBasicZeApisCalled(uint32_t expectedCount, CallbackType stage)
        {
            std::map<std::string, uint32_t> expectedCounts = {
                {"zeDeviceGetCommandQueueGroupProperties", expectedCount},
                {"zeDeviceGetMemoryProperties", expectedCount},
                {"zeDeviceGetMemoryAccessProperties", expectedCount}};
            verifyZeCallbackCounts(expectedCounts, stage);
        }

        void verifyBasicZeApisCalledBothCallbackTypes(uint32_t expectedCount)
        {
            verifyBasicZeApisCalled(expectedCount, CallbackType::PROLOGUE_AND_EPILOGUE);
        }

        // ZER API Callback Functions
        static void zerGetLastErrorDescriptionPrologueCallback(zer_get_last_error_description_params_t *params, ze_result_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZerPrologueCallCount("zerGetLastErrorDescription");
        }

        static void zerTranslateDeviceHandleToIdentifierPrologueCallback(zer_translate_device_handle_to_identifier_params_t *params, uint32_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZerPrologueCallCount("zerTranslateDeviceHandleToIdentifier");
        }

        static void zerTranslateIdentifierToDeviceHandlePrologueCallback(zer_translate_identifier_to_device_handle_params_t *params, ze_device_handle_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZerPrologueCallCount("zerTranslateIdentifierToDeviceHandle");
        }

        static void zerGetDefaultContextPrologueCallback(zer_get_default_context_params_t *params, ze_context_handle_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZerPrologueCallCount("zerGetDefaultContext");
        }

        static void zerGetLastErrorDescriptionEpilogueCallback(zer_get_last_error_description_params_t *params, ze_result_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZerEpilogueCallCount("zerGetLastErrorDescription");
        }

        static void zerTranslateDeviceHandleToIdentifierEpilogueCallback(zer_translate_device_handle_to_identifier_params_t *params, uint32_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZerEpilogueCallCount("zerTranslateDeviceHandleToIdentifier");
        }

        static void zerTranslateIdentifierToDeviceHandleEpilogueCallback(zer_translate_identifier_to_device_handle_params_t *params, ze_device_handle_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZerEpilogueCallCount("zerTranslateIdentifierToDeviceHandle");
        }

        static void zerGetDefaultContextEpilogueCallback(zer_get_default_context_params_t *params, ze_context_handle_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZerEpilogueCallCount("zerGetDefaultContext");
        }

        // ZE API Callback Functions
        static void zeDeviceGetCommandQueueGroupPropertiesPrologueCallback(ze_device_get_command_queue_group_properties_params_t *params, ze_result_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZePrologueCallCount("zeDeviceGetCommandQueueGroupProperties");
        }

        static void zeDeviceGetCommandQueueGroupPropertiesEpilogueCallback(ze_device_get_command_queue_group_properties_params_t *params, ze_result_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZeEpilogueCallCount("zeDeviceGetCommandQueueGroupProperties");
        }

        static void zeDeviceGetMemoryPropertiesPrologueCallback(ze_device_get_memory_properties_params_t *params, ze_result_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZePrologueCallCount("zeDeviceGetMemoryProperties");
        }

        static void zeDeviceGetMemoryPropertiesEpilogueCallback(ze_device_get_memory_properties_params_t *params, ze_result_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZeEpilogueCallCount("zeDeviceGetMemoryProperties");
        }

        static void zeDeviceGetMemoryAccessPropertiesPrologueCallback(ze_device_get_memory_access_properties_params_t *params, ze_result_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZePrologueCallCount("zeDeviceGetMemoryAccessProperties");
        }

        static void zeDeviceGetMemoryAccessPropertiesEpilogueCallback(ze_device_get_memory_access_properties_params_t *params, ze_result_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            TracingData *data = static_cast<TracingData *>(pTracerUserData);
            data->incrementZeEpilogueCallCount("zeDeviceGetMemoryAccessProperties");
        }
    };

    class TracingParameterizedTest : public TracingTest,
                                     public ::testing::WithParamInterface<TracingTest::InitMethod>
    {
    };

    TEST_P(TracingParameterizedTest,
           GivenLoaderWhenCallingZerApisWithStaticTracingEnabledAndPrologueCallbacksRegisteredThenExpectTracingToWork)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerZerPrologueCallbacks(hTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        // Call all ZER APIs
        callAllZerApis();

        verifyAllZerApisCalled(1, CallbackType::PROLOGUE_ONLY);

        callAllZerApis();
        verifyAllZerApisCalled(2, CallbackType::PROLOGUE_ONLY);

        destroyTracer(hTracer);
    }

    TEST_P(TracingParameterizedTest,
           GivenLoaderWhenCallingZerApisWithStaticTracingEnabledAndEpilogueCallbacksRegisteredThenExpectTracingToWork)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerZerEpilogueCallbacks(hTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callAllZerApis();

        verifyAllZerApisCalled(1, CallbackType::EPILOGUE_ONLY);

        callAllZerApis();
        verifyAllZerApisCalled(2, CallbackType::EPILOGUE_ONLY);

        destroyTracer(hTracer);
    }

    TEST_P(TracingParameterizedTest,
           GivenLoaderWhenCallingZerApisWithStaticTracingEnabledAndBothCallbacksRegisteredThenExpectBothToWork)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerZerPrologueCallbacks(hTracer);
        registerZerEpilogueCallbacks(hTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callAllZerApis();

        verifyAllZerApisCalledBothCallbackTypes(1);

        callAllZerApis();
        verifyAllZerApisCalledBothCallbackTypes(2);

        destroyTracer(hTracer);
    }

    TEST_P(TracingParameterizedTest,
           GivenLoaderWhenCallingZerApisWithDynamicTracingEnabledAndPrologueCallbacksRegisteredThenExpectCallbacksToWorkCorrectly)
    {
        InitMethod initMethod = GetParam();

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerZerPrologueCallbacks(hTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callAllZerApis();
        verifyAllZerApisCalled(0, CallbackType::PROLOGUE_ONLY);

        EXPECT_EQ(ZE_RESULT_SUCCESS, enableDynamicTracing());
        callAllZerApis();
        verifyAllZerApisCalled(1, CallbackType::PROLOGUE_ONLY);

        EXPECT_EQ(ZE_RESULT_SUCCESS, disableDynamicTracing());
        callAllZerApis();
        verifyAllZerApisCalled(1, CallbackType::PROLOGUE_ONLY);

        EXPECT_EQ(ZE_RESULT_SUCCESS, enableDynamicTracing());
        const char *errorString = nullptr;
        ze_result_t result = zerGetLastErrorDescription(&errorString);
        EXPECT_EQ(ZE_RESULT_SUCCESS, result);
        EXPECT_TRUE(compare_env("zerGetLastErrorDescription", "1"));
        EXPECT_EQ(2, tracingData.getZerPrologueCallCount("zerGetLastErrorDescription"));

        destroyTracer(hTracer);
    }

    TEST_P(TracingParameterizedTest,
           GivenLoaderWhenCallingZerApisWithDynamicTracingEnabledAndEpilogueCallbacksRegisteredThenExpectTracingToWork)
    {
        InitMethod initMethod = GetParam();

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerZerEpilogueCallbacks(hTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callAllZerApis();
        verifyAllZerApisCalled(0, CallbackType::EPILOGUE_ONLY);

        EXPECT_EQ(ZE_RESULT_SUCCESS, enableDynamicTracing());
        callAllZerApis();
        verifyAllZerApisCalled(1, CallbackType::EPILOGUE_ONLY);

        EXPECT_EQ(ZE_RESULT_SUCCESS, disableDynamicTracing());
        callAllZerApis();
        verifyAllZerApisCalled(1, CallbackType::EPILOGUE_ONLY);

        EXPECT_EQ(ZE_RESULT_SUCCESS, enableDynamicTracing());
        const char *errorString = nullptr;
        ze_result_t result = zerGetLastErrorDescription(&errorString);
        EXPECT_EQ(ZE_RESULT_SUCCESS, result);
        EXPECT_TRUE(compare_env("zerGetLastErrorDescription", "1"));
        EXPECT_EQ(2, tracingData.getZerEpilogueCallCount("zerGetLastErrorDescription"));

        destroyTracer(hTracer);
    }

    TEST_P(TracingParameterizedTest,
           GivenLoaderWhenCallingZerApisWithDynamicTracingEnabledAndBothCallbacksRegisteredThenExpectFullTracingFunctionality)
    {
        InitMethod initMethod = GetParam();

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerZerPrologueCallbacks(hTracer);
        registerZerEpilogueCallbacks(hTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callAllZerApis();
        verifyAllZerApisCalled(0, CallbackType::PROLOGUE_ONLY);
        verifyAllZerApisCalled(0, CallbackType::EPILOGUE_ONLY);

        EXPECT_EQ(ZE_RESULT_SUCCESS, enableDynamicTracing());
        callAllZerApis();
        verifyAllZerApisCalledBothCallbackTypes(1);

        callAllZerApis();
        verifyAllZerApisCalledBothCallbackTypes(2);

        EXPECT_EQ(ZE_RESULT_SUCCESS, disableDynamicTracing());
        callAllZerApis();
        verifyAllZerApisCalledBothCallbackTypes(2);

        destroyTracer(hTracer);
    }

    TEST_P(TracingParameterizedTest,
           GivenLoaderWithStaticTracingEnabledAndMultipleTracersWithBothCallbacksRegisteredWhenCallingZerApisThenAllTracersReceiveCallbacks)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer1 = createTracer();
        zel_tracer_handle_t hTracer2 = createTracer();
        zel_tracer_handle_t hTracer3 = createTracer();

        registerZerPrologueCallbacks(hTracer1);
        registerZerEpilogueCallbacks(hTracer1);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer1, true));

        registerZerPrologueCallbacks(hTracer2);
        registerZerEpilogueCallbacks(hTracer2);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer2, true));

        registerZerPrologueCallbacks(hTracer3);
        registerZerEpilogueCallbacks(hTracer3);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer3, true));

        callAllZerApis();

        verifyAllZerApisCalledBothCallbackTypes(3);

        destroyTracer(hTracer1);
        destroyTracer(hTracer2);
        destroyTracer(hTracer3);
    }

    TEST_P(TracingParameterizedTest,
           GivenLoaderWithStaticTracingEnabledAndMultipleEnabledAndDisabledTracersWithPrologueCallbacksRegisteredWhenCallingZerApisThenOnlyEnabledTracersReceiveCallbacks)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hEnabledTracer1 = createTracer();
        zel_tracer_handle_t hEnabledTracer2 = createTracer();
        zel_tracer_handle_t hDisabledTracer = createTracer();

        registerZerPrologueCallbacks(hEnabledTracer1);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hEnabledTracer1, true));

        registerZerPrologueCallbacks(hEnabledTracer2);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hEnabledTracer2, true));

        registerZerPrologueCallbacks(hDisabledTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hDisabledTracer, false));

        uint32_t initialCount = tracingData.getZerPrologueCallCount("zerGetLastErrorDescription");

        const char *errorString = nullptr;
        ze_result_t result = zerGetLastErrorDescription(&errorString);
        EXPECT_EQ(ZE_RESULT_SUCCESS, result);

        uint32_t finalCount = tracingData.getZerPrologueCallCount("zerGetLastErrorDescription");

        EXPECT_EQ(2, finalCount - initialCount);

        uint32_t beforeEnableCount = tracingData.getZerPrologueCallCount("zerGetLastErrorDescription");
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hDisabledTracer, true));

        result = zerGetLastErrorDescription(&errorString);
        EXPECT_EQ(ZE_RESULT_SUCCESS, result);
        uint32_t afterEnableCount = tracingData.getZerPrologueCallCount("zerGetLastErrorDescription");

        EXPECT_EQ(3, afterEnableCount - beforeEnableCount);

        destroyTracer(hEnabledTracer1);
        destroyTracer(hEnabledTracer2);
        destroyTracer(hDisabledTracer);
    }

    TEST_P(TracingParameterizedTest,
           GivenLoaderWithStaticTracingEnabledAndMultipleTracersWithDifferentCallbacksRegisteredWhenCallingZerApisThenEachTracerWorksIndependently)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hPrologueTracer = createTracer();
        zel_tracer_handle_t hEpilogueTracer = createTracer();
        zel_tracer_handle_t hBothTracer = createTracer();

        registerZerPrologueCallbacks(hPrologueTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hPrologueTracer, true));

        registerZerEpilogueCallbacks(hEpilogueTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hEpilogueTracer, true));

        registerZerPrologueCallbacks(hBothTracer);
        registerZerEpilogueCallbacks(hBothTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hBothTracer, true));

        callAllZerApis();
        verifyAllZerApisCalled(2, CallbackType::PROLOGUE_ONLY);
        verifyAllZerApisCalled(2, CallbackType::EPILOGUE_ONLY);

        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hPrologueTracer, false));

        uint32_t prologueCountBefore = tracingData.getZerPrologueCallCount("zerGetLastErrorDescription");
        uint32_t epilogueCountBefore = tracingData.getZerEpilogueCallCount("zerGetLastErrorDescription");

        callAllZerApis();

        uint32_t prologueCountAfter = tracingData.getZerPrologueCallCount("zerGetLastErrorDescription");
        uint32_t epilogueCountAfter = tracingData.getZerEpilogueCallCount("zerGetLastErrorDescription");

        EXPECT_EQ(1, prologueCountAfter - prologueCountBefore);
        EXPECT_EQ(2, epilogueCountAfter - epilogueCountBefore);

        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hEpilogueTracer, false));

        prologueCountBefore = tracingData.getZerPrologueCallCount("zerGetLastErrorDescription");
        epilogueCountBefore = tracingData.getZerEpilogueCallCount("zerGetLastErrorDescription");

        callAllZerApis();

        prologueCountAfter = tracingData.getZerPrologueCallCount("zerGetLastErrorDescription");
        epilogueCountAfter = tracingData.getZerEpilogueCallCount("zerGetLastErrorDescription");

        EXPECT_EQ(1, prologueCountAfter - prologueCountBefore);
        EXPECT_EQ(1, epilogueCountAfter - epilogueCountBefore);

        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hPrologueTracer, true));
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hEpilogueTracer, true));

        prologueCountBefore = tracingData.getZerPrologueCallCount("zerGetLastErrorDescription");
        epilogueCountBefore = tracingData.getZerEpilogueCallCount("zerGetLastErrorDescription");

        callAllZerApis();

        prologueCountAfter = tracingData.getZerPrologueCallCount("zerGetLastErrorDescription");
        epilogueCountAfter = tracingData.getZerEpilogueCallCount("zerGetLastErrorDescription");

        EXPECT_EQ(2, prologueCountAfter - prologueCountBefore);
        EXPECT_EQ(2, epilogueCountAfter - epilogueCountBefore);

        destroyTracer(hPrologueTracer);
        destroyTracer(hEpilogueTracer);
        destroyTracer(hBothTracer);
    }

    TEST_P(TracingParameterizedTest,
           GivenLoaderWithStaticTracingEnabledAndSelectiveCallbackRegistrationWhenCallingZerApisThenOnlyRegisteredCallbacksAreTriggered)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();

        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerGetLastErrorDescriptionRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                      +TracingTest::zerGetLastErrorDescriptionPrologueCallback));
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerTranslateIdentifierToDeviceHandleRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                                +TracingTest::zerTranslateIdentifierToDeviceHandlePrologueCallback));

        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerGetLastErrorDescriptionRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                      +TracingTest::zerGetLastErrorDescriptionEpilogueCallback));

        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callAllZerApis();

        EXPECT_EQ(1, tracingData.getZerPrologueCallCount("zerGetLastErrorDescription"));
        EXPECT_EQ(1, tracingData.getZerPrologueCallCount("zerTranslateIdentifierToDeviceHandle"));
        EXPECT_EQ(0, tracingData.getZerPrologueCallCount("zerTranslateDeviceHandleToIdentifier"));
        EXPECT_EQ(0, tracingData.getZerPrologueCallCount("zerGetDefaultContext"));

        EXPECT_EQ(1, tracingData.getZerEpilogueCallCount("zerGetLastErrorDescription"));
        EXPECT_EQ(0, tracingData.getZerEpilogueCallCount("zerTranslateDeviceHandleToIdentifier"));
        EXPECT_EQ(0, tracingData.getZerEpilogueCallCount("zerTranslateIdentifierToDeviceHandle"));
        EXPECT_EQ(0, tracingData.getZerEpilogueCallCount("zerGetDefaultContext"));

        callAllZerApis();

        EXPECT_EQ(2, tracingData.getZerPrologueCallCount("zerGetLastErrorDescription"));
        EXPECT_EQ(2, tracingData.getZerPrologueCallCount("zerTranslateIdentifierToDeviceHandle"));
        EXPECT_EQ(0, tracingData.getZerPrologueCallCount("zerTranslateDeviceHandleToIdentifier"));
        EXPECT_EQ(0, tracingData.getZerPrologueCallCount("zerGetDefaultContext"));
        EXPECT_EQ(2, tracingData.getZerEpilogueCallCount("zerGetLastErrorDescription"));
        EXPECT_EQ(0, tracingData.getZerEpilogueCallCount("zerTranslateDeviceHandleToIdentifier"));
        EXPECT_EQ(0, tracingData.getZerEpilogueCallCount("zerTranslateIdentifierToDeviceHandle"));
        EXPECT_EQ(0, tracingData.getZerEpilogueCallCount("zerGetDefaultContext"));
        destroyTracer(hTracer);
    }

    TEST_P(TracingParameterizedTest,
           GivenLoaderWithStaticTracingEnabledAndBothZeAndZerCallbacksRegisteredWhenCallingBothApisThenBothAreTraced)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();

        registerZerPrologueCallbacks(hTracer);
        registerZerEpilogueCallbacks(hTracer);
        registerZePrologueCallbacks(hTracer);
        registerZeEpilogueCallbacks(hTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callAllZerApis();
        callBasicZeApis(drivers);

        verifyAllZerApisCalled(1, CallbackType::PROLOGUE_AND_EPILOGUE);
        verifyBasicZeApisCalled(1, CallbackType::PROLOGUE_AND_EPILOGUE);

        callAllZerApis();
        callBasicZeApis(drivers);

        verifyAllZerApisCalled(2, CallbackType::PROLOGUE_AND_EPILOGUE);
        verifyBasicZeApisCalled(2, CallbackType::PROLOGUE_AND_EPILOGUE);

        destroyTracer(hTracer);
    }

    TEST_P(TracingParameterizedTest,
           GivenLoaderWithDynamicTracingEnabledAndBothZeAndZerCallbacksRegisteredWhenCallingBothApisThenBothAreTraced)
    {
        InitMethod initMethod = GetParam();

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerZerPrologueCallbacks(hTracer);
        registerZerEpilogueCallbacks(hTracer);
        registerZePrologueCallbacks(hTracer);
        registerZeEpilogueCallbacks(hTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callAllZerApis();
        callBasicZeApis(drivers);
        verifyAllZerApisCalledBothCallbackTypes(0);
        verifyBasicZeApisCalledBothCallbackTypes(0);

        EXPECT_EQ(ZE_RESULT_SUCCESS, enableDynamicTracing());
        callAllZerApis();
        callBasicZeApis(drivers);
        verifyAllZerApisCalledBothCallbackTypes(1);
        verifyBasicZeApisCalledBothCallbackTypes(1);

        EXPECT_EQ(ZE_RESULT_SUCCESS, disableDynamicTracing());
        callAllZerApis();
        callBasicZeApis(drivers);
        verifyAllZerApisCalledBothCallbackTypes(1);
        verifyBasicZeApisCalledBothCallbackTypes(1);

        EXPECT_EQ(ZE_RESULT_SUCCESS, enableDynamicTracing());
        const char *errorString = nullptr;
        ze_result_t result = zerGetLastErrorDescription(&errorString);
        EXPECT_EQ(ZE_RESULT_SUCCESS, result);
        EXPECT_EQ(2, tracingData.getZerPrologueCallCount("zerGetLastErrorDescription"));
        EXPECT_EQ(2, tracingData.getZerEpilogueCallCount("zerGetLastErrorDescription"));

        uint32_t deviceCount = 1;
        std::vector<ze_device_handle_t> devices(deviceCount);
        result = zeDeviceGet(drivers[0], &deviceCount, devices.data());
        EXPECT_EQ(ZE_RESULT_SUCCESS, result);

        uint32_t queueGroupCount = 0;
        result = zeDeviceGetCommandQueueGroupProperties(devices[0], &queueGroupCount, nullptr);
        EXPECT_EQ(ZE_RESULT_SUCCESS, result);
        EXPECT_EQ(2, tracingData.getZePrologueCallCount("zeDeviceGetCommandQueueGroupProperties"));
        EXPECT_EQ(2, tracingData.getZeEpilogueCallCount("zeDeviceGetCommandQueueGroupProperties"));

        destroyTracer(hTracer);
    }

    TEST_P(TracingParameterizedTest,
           GivenLoaderWithDynamicTracingEnabledAndZerApisUnsupportedAndBothZeAndZerCallbacksRegisteredWhenCallingBothApisThenTracingWorksForZeAndZerCallbacksAreStillInvoked)
    {
        putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_DISABLE_ZER_API=1"));
        InitMethod initMethod = GetParam();

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerZerPrologueCallbacks(hTracer);
        registerZerEpilogueCallbacks(hTracer);
        registerZePrologueCallbacks(hTracer);
        registerZeEpilogueCallbacks(hTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callBasicZeApis(drivers);
        verifyBasicZeApisCalledBothCallbackTypes(0);

        EXPECT_EQ(ZE_RESULT_SUCCESS, enableDynamicTracing());

        const char *errorString = nullptr;
        ze_result_t result = zerGetLastErrorDescription(&errorString);
        EXPECT_EQ(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, result);
        // ZER callbacks should still be called in the tracing layer even if the driver ends up not supporting ZER APIs
        EXPECT_EQ(1, tracingData.getZerPrologueCallCount("zerGetLastErrorDescription"));
        EXPECT_EQ(1, tracingData.getZerEpilogueCallCount("zerGetLastErrorDescription"));

        callBasicZeApis(drivers);
        verifyBasicZeApisCalledBothCallbackTypes(1);

        EXPECT_EQ(ZE_RESULT_SUCCESS, disableDynamicTracing());
        callBasicZeApis(drivers);
        verifyBasicZeApisCalledBothCallbackTypes(1);

        EXPECT_EQ(ZE_RESULT_SUCCESS, enableDynamicTracing());

        errorString = nullptr;
        result = zerGetLastErrorDescription(&errorString);
        EXPECT_EQ(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, result);
        // ZER callbacks should still be called in the tracing layer even if the driver ends up not supporting ZER APIs
        EXPECT_EQ(2, tracingData.getZerPrologueCallCount("zerGetLastErrorDescription"));
        EXPECT_EQ(2, tracingData.getZerEpilogueCallCount("zerGetLastErrorDescription"));

        uint32_t deviceCount = 1;
        std::vector<ze_device_handle_t> devices(deviceCount);
        result = zeDeviceGet(drivers[0], &deviceCount, devices.data());
        EXPECT_EQ(ZE_RESULT_SUCCESS, result);

        uint32_t queueGroupCount = 0;
        result = zeDeviceGetCommandQueueGroupProperties(devices[0], &queueGroupCount, nullptr);
        EXPECT_EQ(ZE_RESULT_SUCCESS, result);
        EXPECT_EQ(2, tracingData.getZePrologueCallCount("zeDeviceGetCommandQueueGroupProperties"));
        EXPECT_EQ(2, tracingData.getZeEpilogueCallCount("zeDeviceGetCommandQueueGroupProperties"));

        destroyTracer(hTracer);
    }

    INSTANTIATE_TEST_SUITE_P(
        InitMethods,
        TracingParameterizedTest,
        ::testing::Values(
            TracingTest::InitMethod::ZEINIT,
            TracingTest::InitMethod::ZEINIT_DRIVERS));

} // namespace