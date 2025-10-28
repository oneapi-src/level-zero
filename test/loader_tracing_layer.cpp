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

    class ZerTracingTest : public ::testing::Test
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
        struct ZerTracingData
        {
            std::map<std::string, uint32_t> prologueCallCounts;
            std::map<std::string, uint32_t> epilogueCallCounts;
            bool dynamicTracingEnabled = false;

            void reset()
            {
                prologueCallCounts.clear();
                epilogueCallCounts.clear();
                dynamicTracingEnabled = false;
            }

            void incrementPrologueCallCount(const std::string &apiName)
            {
                prologueCallCounts[apiName]++;
            }

            void incrementEpilogueCallCount(const std::string &apiName)
            {
                epilogueCallCounts[apiName]++;
            }

            uint32_t getPrologueCallCount(const std::string &apiName) const
            {
                auto it = prologueCallCounts.find(apiName);
                return (it != prologueCallCounts.end()) ? it->second : 0;
            }

            uint32_t getEpilogueCallCount(const std::string &apiName) const
            {
                auto it = epilogueCallCounts.find(apiName);
                return (it != epilogueCallCounts.end()) ? it->second : 0;
            }
        };

        ZerTracingData tracingData;

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

        void registerPrologueCallbacks(zel_tracer_handle_t hTracer)
        {
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerGetLastErrorDescriptionRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                          +ZerTracingTest::zerGetLastErrorDescriptionPrologueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerTranslateDeviceHandleToIdentifierRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                                    +ZerTracingTest::zerTranslateDeviceHandleToIdentifierPrologueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerTranslateIdentifierToDeviceHandleRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                                    +ZerTracingTest::zerTranslateIdentifierToDeviceHandlePrologueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerGetDefaultContextRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                    +ZerTracingTest::zerGetDefaultContextPrologueCallback));
        }

        void registerEpilogueCallbacks(zel_tracer_handle_t hTracer)
        {
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerGetLastErrorDescriptionRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                          +ZerTracingTest::zerGetLastErrorDescriptionEpilogueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerTranslateDeviceHandleToIdentifierRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                                    +ZerTracingTest::zerTranslateDeviceHandleToIdentifierEpilogueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerTranslateIdentifierToDeviceHandleRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                                    +ZerTracingTest::zerTranslateIdentifierToDeviceHandleEpilogueCallback));
            EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerGetDefaultContextRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                    +ZerTracingTest::zerGetDefaultContextEpilogueCallback));
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

        void verifyCallbackCounts(const std::map<std::string, uint32_t> &expectedCounts, CallbackType stage)
        {
            for (const auto &expected : expectedCounts)
            {
                if (stage == CallbackType::PROLOGUE_ONLY || stage == CallbackType::PROLOGUE_AND_EPILOGUE)
                {
                    uint32_t actualCount = tracingData.getPrologueCallCount(expected.first);
                    EXPECT_EQ(expected.second, actualCount);
                }

                if (stage == CallbackType::EPILOGUE_ONLY || stage == CallbackType::PROLOGUE_AND_EPILOGUE)
                {
                    uint32_t actualCount = tracingData.getEpilogueCallCount(expected.first);
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
            verifyCallbackCounts(expectedCounts, stage);
        }

        void verifyAllZerApisCalledBothCallbackTypes(uint32_t expectedCount)
        {
            verifyAllZerApisCalled(expectedCount, CallbackType::PROLOGUE_AND_EPILOGUE);
        }

        static void zerGetLastErrorDescriptionPrologueCallback(zer_get_last_error_description_params_t *params, ze_result_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            ZerTracingData *data = static_cast<ZerTracingData *>(pTracerUserData);
            data->incrementPrologueCallCount("zerGetLastErrorDescription");
        }

        static void zerTranslateDeviceHandleToIdentifierPrologueCallback(zer_translate_device_handle_to_identifier_params_t *params, uint32_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            ZerTracingData *data = static_cast<ZerTracingData *>(pTracerUserData);
            data->incrementPrologueCallCount("zerTranslateDeviceHandleToIdentifier");
        }

        static void zerTranslateIdentifierToDeviceHandlePrologueCallback(zer_translate_identifier_to_device_handle_params_t *params, ze_device_handle_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            ZerTracingData *data = static_cast<ZerTracingData *>(pTracerUserData);
            data->incrementPrologueCallCount("zerTranslateIdentifierToDeviceHandle");
        }

        static void zerGetDefaultContextPrologueCallback(zer_get_default_context_params_t *params, ze_context_handle_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            ZerTracingData *data = static_cast<ZerTracingData *>(pTracerUserData);
            data->incrementPrologueCallCount("zerGetDefaultContext");
        }

        static void zerGetLastErrorDescriptionEpilogueCallback(zer_get_last_error_description_params_t *params, ze_result_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            ZerTracingData *data = static_cast<ZerTracingData *>(pTracerUserData);
            data->incrementEpilogueCallCount("zerGetLastErrorDescription");
        }

        static void zerTranslateDeviceHandleToIdentifierEpilogueCallback(zer_translate_device_handle_to_identifier_params_t *params, uint32_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            ZerTracingData *data = static_cast<ZerTracingData *>(pTracerUserData);
            data->incrementEpilogueCallCount("zerTranslateDeviceHandleToIdentifier");
        }

        static void zerTranslateIdentifierToDeviceHandleEpilogueCallback(zer_translate_identifier_to_device_handle_params_t *params, ze_device_handle_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            ZerTracingData *data = static_cast<ZerTracingData *>(pTracerUserData);
            data->incrementEpilogueCallCount("zerTranslateIdentifierToDeviceHandle");
        }

        static void zerGetDefaultContextEpilogueCallback(zer_get_default_context_params_t *params, ze_context_handle_t result, void *pTracerUserData, void **ppTracerInstanceUserData)
        {
            ZerTracingData *data = static_cast<ZerTracingData *>(pTracerUserData);
            data->incrementEpilogueCallCount("zerGetDefaultContext");
        }
    };

    class ZerTracingParameterizedTest : public ZerTracingTest,
                                        public ::testing::WithParamInterface<ZerTracingTest::InitMethod>
    {
    };

    TEST_P(ZerTracingParameterizedTest,
           GivenLoaderWhenCallingZerApisWithStaticTracingEnabledAndPrologueCallbacksRegisteredThenExpectTracingToWork)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerPrologueCallbacks(hTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callAllZerApis();

        verifyAllZerApisCalled(1, CallbackType::PROLOGUE_ONLY);

        callAllZerApis();
        verifyAllZerApisCalled(2, CallbackType::PROLOGUE_ONLY);

        destroyTracer(hTracer);
    }

    TEST_P(ZerTracingParameterizedTest,
           GivenLoaderWhenCallingZerApisWithStaticTracingEnabledAndEpilogueCallbacksRegisteredThenExpectTracingToWork)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerEpilogueCallbacks(hTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callAllZerApis();

        verifyAllZerApisCalled(1, CallbackType::EPILOGUE_ONLY);

        callAllZerApis();
        verifyAllZerApisCalled(2, CallbackType::EPILOGUE_ONLY);

        destroyTracer(hTracer);
    }

    TEST_P(ZerTracingParameterizedTest,
           GivenLoaderWhenCallingZerApisWithStaticTracingEnabledAndBothCallbacksRegisteredThenExpectBothToWork)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerPrologueCallbacks(hTracer);
        registerEpilogueCallbacks(hTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callAllZerApis();

        verifyAllZerApisCalledBothCallbackTypes(1);

        callAllZerApis();
        verifyAllZerApisCalledBothCallbackTypes(2);

        destroyTracer(hTracer);
    }

    TEST_P(ZerTracingParameterizedTest,
           GivenLoaderWhenCallingZerApisWithDynamicTracingEnabledAndPrologueCallbacksRegisteredThenExpectCallbacksToWorkCorrectly)
    {
        InitMethod initMethod = GetParam();

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerPrologueCallbacks(hTracer);
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
        EXPECT_EQ(2, tracingData.getPrologueCallCount("zerGetLastErrorDescription"));

        destroyTracer(hTracer);
    }

    TEST_P(ZerTracingParameterizedTest,
           GivenLoaderWhenCallingZerApisWithDynamicTracingEnabledAndEpilogueCallbacksRegisteredThenExpectTracingToWork)
    {
        InitMethod initMethod = GetParam();

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerEpilogueCallbacks(hTracer);
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
        EXPECT_EQ(2, tracingData.getEpilogueCallCount("zerGetLastErrorDescription"));

        destroyTracer(hTracer);
    }

    TEST_P(ZerTracingParameterizedTest,
           GivenLoaderWhenCallingZerApisWithDynamicTracingEnabledAndBothCallbacksRegisteredThenExpectFullTracingFunctionality)
    {
        InitMethod initMethod = GetParam();

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();
        registerPrologueCallbacks(hTracer);
        registerEpilogueCallbacks(hTracer);
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

    TEST_P(ZerTracingParameterizedTest,
           GivenLoaderWithStaticTracingEnabledAndMultipleTracersWithBothCallbacksRegisteredWhenCallingZerApisThenAllTracersReceiveCallbacks)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer1 = createTracer();
        zel_tracer_handle_t hTracer2 = createTracer();
        zel_tracer_handle_t hTracer3 = createTracer();

        registerPrologueCallbacks(hTracer1);
        registerEpilogueCallbacks(hTracer1);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer1, true));

        registerPrologueCallbacks(hTracer2);
        registerEpilogueCallbacks(hTracer2);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer2, true));

        registerPrologueCallbacks(hTracer3);
        registerEpilogueCallbacks(hTracer3);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer3, true));

        callAllZerApis();

        verifyAllZerApisCalledBothCallbackTypes(3);

        destroyTracer(hTracer1);
        destroyTracer(hTracer2);
        destroyTracer(hTracer3);
    }

    TEST_P(ZerTracingParameterizedTest,
           GivenLoaderWithStaticTracingEnabledAndMultipleEnabledAndDisabledTracersWithPrologueCallbacksRegisteredWhenCallingZerApisThenOnlyEnabledTracersReceiveCallbacks)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hEnabledTracer1 = createTracer();
        zel_tracer_handle_t hEnabledTracer2 = createTracer();
        zel_tracer_handle_t hDisabledTracer = createTracer();

        registerPrologueCallbacks(hEnabledTracer1);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hEnabledTracer1, true));

        registerPrologueCallbacks(hEnabledTracer2);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hEnabledTracer2, true));

        registerPrologueCallbacks(hDisabledTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hDisabledTracer, false));

        uint32_t initialCount = tracingData.getPrologueCallCount("zerGetLastErrorDescription");

        const char *errorString = nullptr;
        ze_result_t result = zerGetLastErrorDescription(&errorString);
        EXPECT_EQ(ZE_RESULT_SUCCESS, result);

        uint32_t finalCount = tracingData.getPrologueCallCount("zerGetLastErrorDescription");

        EXPECT_EQ(2, finalCount - initialCount);

        uint32_t beforeEnableCount = tracingData.getPrologueCallCount("zerGetLastErrorDescription");
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hDisabledTracer, true));

        result = zerGetLastErrorDescription(&errorString);
        EXPECT_EQ(ZE_RESULT_SUCCESS, result);
        uint32_t afterEnableCount = tracingData.getPrologueCallCount("zerGetLastErrorDescription");

        EXPECT_EQ(3, afterEnableCount - beforeEnableCount);

        destroyTracer(hEnabledTracer1);
        destroyTracer(hEnabledTracer2);
        destroyTracer(hDisabledTracer);
    }

    TEST_P(ZerTracingParameterizedTest,
           GivenLoaderWithStaticTracingEnabledAndMultipleTracersWithDifferentCallbacksRegisteredWhenCallingZerApisThenEachTracerWorksIndependently)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hPrologueTracer = createTracer();
        zel_tracer_handle_t hEpilogueTracer = createTracer();
        zel_tracer_handle_t hBothTracer = createTracer();

        registerPrologueCallbacks(hPrologueTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hPrologueTracer, true));

        registerEpilogueCallbacks(hEpilogueTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hEpilogueTracer, true));

        registerPrologueCallbacks(hBothTracer);
        registerEpilogueCallbacks(hBothTracer);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hBothTracer, true));

        callAllZerApis();
        verifyAllZerApisCalled(2, CallbackType::PROLOGUE_ONLY);
        verifyAllZerApisCalled(2, CallbackType::EPILOGUE_ONLY);

        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hPrologueTracer, false));

        uint32_t prologueCountBefore = tracingData.getPrologueCallCount("zerGetLastErrorDescription");
        uint32_t epilogueCountBefore = tracingData.getEpilogueCallCount("zerGetLastErrorDescription");

        callAllZerApis();

        uint32_t prologueCountAfter = tracingData.getPrologueCallCount("zerGetLastErrorDescription");
        uint32_t epilogueCountAfter = tracingData.getEpilogueCallCount("zerGetLastErrorDescription");

        EXPECT_EQ(1, prologueCountAfter - prologueCountBefore);
        EXPECT_EQ(2, epilogueCountAfter - epilogueCountBefore);

        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hEpilogueTracer, false));

        prologueCountBefore = tracingData.getPrologueCallCount("zerGetLastErrorDescription");
        epilogueCountBefore = tracingData.getEpilogueCallCount("zerGetLastErrorDescription");

        callAllZerApis();

        prologueCountAfter = tracingData.getPrologueCallCount("zerGetLastErrorDescription");
        epilogueCountAfter = tracingData.getEpilogueCallCount("zerGetLastErrorDescription");

        EXPECT_EQ(1, prologueCountAfter - prologueCountBefore);
        EXPECT_EQ(1, epilogueCountAfter - epilogueCountBefore);

        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hPrologueTracer, true));
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hEpilogueTracer, true));

        prologueCountBefore = tracingData.getPrologueCallCount("zerGetLastErrorDescription");
        epilogueCountBefore = tracingData.getEpilogueCallCount("zerGetLastErrorDescription");

        callAllZerApis();

        prologueCountAfter = tracingData.getPrologueCallCount("zerGetLastErrorDescription");
        epilogueCountAfter = tracingData.getEpilogueCallCount("zerGetLastErrorDescription");

        EXPECT_EQ(2, prologueCountAfter - prologueCountBefore);
        EXPECT_EQ(2, epilogueCountAfter - epilogueCountBefore);

        destroyTracer(hPrologueTracer);
        destroyTracer(hEpilogueTracer);
        destroyTracer(hBothTracer);
    }

    TEST_P(ZerTracingParameterizedTest,
           GivenLoaderWithStaticTracingEnabledAndSelectiveCallbackRegistrationWhenCallingZerApisThenOnlyRegisteredCallbacksAreTriggered)
    {
        InitMethod initMethod = GetParam();

        setupTracing(TracingMode::STATIC_TRACING);

        std::vector<ze_driver_handle_t> drivers;
        initializeLevelZero(initMethod, drivers);

        zel_tracer_handle_t hTracer = createTracer();

        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerGetLastErrorDescriptionRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                      +ZerTracingTest::zerGetLastErrorDescriptionPrologueCallback));
        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerTranslateIdentifierToDeviceHandleRegisterCallback(hTracer, ZEL_REGISTER_PROLOGUE,
                                                                                                +ZerTracingTest::zerTranslateIdentifierToDeviceHandlePrologueCallback));

        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerGetLastErrorDescriptionRegisterCallback(hTracer, ZEL_REGISTER_EPILOGUE,
                                                                                      +ZerTracingTest::zerGetLastErrorDescriptionEpilogueCallback));

        EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

        callAllZerApis();

        EXPECT_EQ(1, tracingData.getPrologueCallCount("zerGetLastErrorDescription"));
        EXPECT_EQ(1, tracingData.getPrologueCallCount("zerTranslateIdentifierToDeviceHandle"));

        EXPECT_EQ(0, tracingData.getPrologueCallCount("zerTranslateDeviceHandleToIdentifier"));
        EXPECT_EQ(0, tracingData.getPrologueCallCount("zerGetDefaultContext"));

        EXPECT_EQ(1, tracingData.getEpilogueCallCount("zerGetLastErrorDescription"));
        EXPECT_EQ(0, tracingData.getEpilogueCallCount("zerTranslateDeviceHandleToIdentifier"));
        EXPECT_EQ(0, tracingData.getEpilogueCallCount("zerTranslateIdentifierToDeviceHandle"));
        EXPECT_EQ(0, tracingData.getEpilogueCallCount("zerGetDefaultContext"));

        callAllZerApis();

        EXPECT_EQ(2, tracingData.getPrologueCallCount("zerGetLastErrorDescription"));
        EXPECT_EQ(2, tracingData.getPrologueCallCount("zerTranslateIdentifierToDeviceHandle"));
        EXPECT_EQ(0, tracingData.getPrologueCallCount("zerTranslateDeviceHandleToIdentifier"));
        EXPECT_EQ(0, tracingData.getPrologueCallCount("zerGetDefaultContext"));
        EXPECT_EQ(2, tracingData.getEpilogueCallCount("zerGetLastErrorDescription"));
        EXPECT_EQ(0, tracingData.getEpilogueCallCount("zerTranslateDeviceHandleToIdentifier"));
        EXPECT_EQ(0, tracingData.getEpilogueCallCount("zerTranslateIdentifierToDeviceHandle"));
        EXPECT_EQ(0, tracingData.getEpilogueCallCount("zerGetDefaultContext"));
        destroyTracer(hTracer);
    }

    INSTANTIATE_TEST_SUITE_P(
        InitMethods,
        ZerTracingParameterizedTest,
        ::testing::Values(
            ZerTracingTest::InitMethod::ZEINIT,
            ZerTracingTest::InitMethod::ZEINIT_DRIVERS));

} // namespace