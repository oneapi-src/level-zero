/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_libapi.cpp
 *
 * @brief C++ static library for zes
 *
 */
#include "ze_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties about the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesDeviceGetProperties(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_device_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Device.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hDevice, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about the state of the device - if a reset is
///        required, reasons for the reset and if the device has been repaired
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesDeviceGetState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_device_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
    )
{
    auto pfnGetState = ze_lib::context->zesDdiTable.Device.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hDevice, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset device
/// 
/// @details
///     - Performs a PCI bus reset of the device. This will result in all
///       current device state being lost.
///     - All applications using the device should be stopped before calling
///       this function.
///     - If the force argument is specified, all applications using the device
///       will be forcibly killed.
///     - The function will block until the device has restarted or a timeout
///       occurred waiting for the reset to complete.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE - "Reset cannot be performed because applications are using this device."
///     - ::ZE_RESULT_ERROR_UNKNOWN - "There were problems unloading the device driver, performing a bus reset or reloading the device driver."
ze_result_t ZE_APICALL
zesDeviceReset(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
    ze_bool_t force                                 ///< [in] If set to true, all applications that are currently using the
                                                    ///< device will be forcibly killed.
    )
{
    auto pfnReset = ze_lib::context->zesDdiTable.Device.pfnReset;
    if( nullptr == pfnReset )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnReset( hDevice, force );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about host processes using the device
/// 
/// @details
///     - The number of processes connected to the device is dynamic. This means
///       that between a call to determine the value of pCount and the
///       subsequent call, the number of processes may have increased or
///       decreased. It is recommended that a large array be passed in so as to
///       avoid receiving the error ::ZE_RESULT_ERROR_INVALID_SIZE. Also, always
///       check the returned value in pCount since it may be less than the
///       earlier call to get the required array size.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + The provided value of pCount is not big enough to store information about all the processes currently attached to the device.
ze_result_t ZE_APICALL
zesDeviceProcessesGetState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of processes currently attached to the device.
                                                    ///< if count is greater than the number of processes currently attached to
                                                    ///< the device, then the driver shall update the value with the correct
                                                    ///< number of processes.
    zes_process_state_t* pProcesses                 ///< [in,out][optional][range(0, *pCount)] array of process information.
                                                    ///< if count is less than the number of processes currently attached to
                                                    ///< the device, then the driver shall only retrieve information about that
                                                    ///< number of processes. In this case, the return code will ::ZE_RESULT_ERROR_INVALID_SIZE.
    )
{
    auto pfnProcessesGetState = ze_lib::context->zesDdiTable.Device.pfnProcessesGetState;
    if( nullptr == pfnProcessesGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnProcessesGetState( hDevice, pCount, pProcesses );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI properties - address, max speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesDevicePciGetProperties(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
    )
{
    auto pfnPciGetProperties = ze_lib::context->zesDdiTable.Device.pfnPciGetProperties;
    if( nullptr == pfnPciGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetProperties( hDevice, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current PCI state - current speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesDevicePciGetState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
    )
{
    auto pfnPciGetState = ze_lib::context->zesDdiTable.Device.pfnPciGetState;
    if( nullptr == pfnPciGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetState( hDevice, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about each configured bar
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDevicePciGetBars(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of PCI bars that are setup.
                                                    ///< if count is greater than the number of PCI bars that are setup, then
                                                    ///< the driver shall update the value with the correct number of PCI bars.
    zes_pci_bar_properties_t* pProperties           ///< [in,out][optional][range(0, *pCount)] array of information about setup
                                                    ///< PCI bars.
                                                    ///< if count is less than the number of PCI bars that are setup, then the
                                                    ///< driver shall only retrieve information about that number of PCI bars.
    )
{
    auto pfnPciGetBars = ze_lib::context->zesDdiTable.Device.pfnPciGetBars;
    if( nullptr == pfnPciGetBars )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetBars( hDevice, pCount, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI stats - bandwidth, number of packets, number of replays
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pStats`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t ZE_APICALL
zesDevicePciGetStats(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
    )
{
    auto pfnPciGetStats = ze_lib::context->zesDdiTable.Device.pfnPciGetStats;
    if( nullptr == pfnPciGetStats )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetStats( hDevice, pStats );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of diagnostics test suites
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumDiagnosticTestSuites(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_diag_handle_t* phDiagnostics                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumDiagnosticTestSuites = ze_lib::context->zesDdiTable.Device.pfnEnumDiagnosticTestSuites;
    if( nullptr == pfnEnumDiagnosticTestSuites )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties of a diagnostics test suite
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesDiagnosticsGetProperties(
    zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
    zes_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                    ///< suite
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Diagnostics.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hDiagnostics, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get individual tests that can be run separately. Not all test suites
///        permit running individual tests - check
///        ::zes_diag_properties_t.haveTests
/// 
/// @details
///     - The list of available tests is returned in order of increasing test
///       index ::zes_diag_test_t.index.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDiagnosticsGetTests(
    zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of tests that are available.
                                                    ///< if count is greater than the number of tests that are available, then
                                                    ///< the driver shall update the value with the correct number of tests.
    zes_diag_test_t* pTests                         ///< [in,out][optional][range(0, *pCount)] array of information about
                                                    ///< individual tests sorted by increasing value of ::zes_diag_test_t.index.
                                                    ///< if count is less than the number of tests that are available, then the
                                                    ///< driver shall only retrieve that number of tests.
    )
{
    auto pfnGetTests = ze_lib::context->zesDdiTable.Diagnostics.pfnGetTests;
    if( nullptr == pfnGetTests )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetTests( hDiagnostics, pCount, pTests );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Run a diagnostics test suite, either all tests or a subset of tests.
/// 
/// @details
///     - WARNING: Performancing diagnostics may destroy current device state
///       information. Gracefully close any running workloads before initiating.
///     - To run all tests in a test suite, set start =
///       ::ZES_DIAG_FIRST_TEST_INDEX and end = ::ZES_DIAG_LAST_TEST_INDEX.
///     - If the test suite permits running individual tests,
///       ::zes_diag_properties_t.haveTests will be true. In this case, the
///       function ::zesDiagnosticsGetTests() can be called to get the list of
///       tests and corresponding indices that can be supplied to the arguments
///       start and end in this function.
///     - This function will block until the diagnostics have completed.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pResult`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform diagnostics.
ze_result_t ZE_APICALL
zesDiagnosticsRunTests(
    zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
    uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                    ///< ::ZES_DIAG_FIRST_TEST_INDEX to start from the beginning.
    uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                    ///< ::ZES_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
    zes_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
    )
{
    auto pfnRunTests = ze_lib::context->zesDdiTable.Diagnostics.pfnRunTests;
    if( nullptr == pfnRunTests )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnRunTests( hDiagnostics, start, end, pResult );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of engine groups
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumEngineGroups(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_engine_handle_t* phEngine                   ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumEngineGroups = ze_lib::context->zesDdiTable.Device.pfnEnumEngineGroups;
    if( nullptr == pfnEnumEngineGroups )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumEngineGroups( hDevice, pCount, phEngine );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get engine group properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesEngineGetProperties(
    zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
    zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Engine.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hEngine, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the activity stats for an engine group
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pStats`
ze_result_t ZE_APICALL
zesEngineGetActivity(
    zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
    zes_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                    ///< counters.
    )
{
    auto pfnGetActivity = ze_lib::context->zesDdiTable.Engine.pfnGetActivity;
    if( nullptr == pfnGetActivity )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetActivity( hEngine, pStats );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Specify the list of events to listen to for a given device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7fff < events`
ze_result_t ZE_APICALL
zesDeviceEventRegister(
    zes_device_handle_t hDevice,                    ///< [in] The device handle.
    zes_event_type_flags_t events                   ///< [in] List of events to listen to.
    )
{
    auto pfnEventRegister = ze_lib::context->zesDdiTable.Device.pfnEventRegister;
    if( nullptr == pfnEventRegister )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEventRegister( hDevice, events );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Wait for events to be received from a one or more devices.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phDevices`
///         + `nullptr == pNumDeviceEvents`
///         + `nullptr == pEvents`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to listen to events.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or more of the supplied device handles belongs to a different driver.
ze_result_t ZE_APICALL
zesDriverEventListen(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then will check status and return immediately;
                                                    ///< if UINT32_MAX, then function will not return until events arrive.
    uint32_t count,                                 ///< [in] Number of device handles in phDevices.
    zes_device_handle_t* phDevices,                 ///< [in][range(0, count)] Device handles to listen to for events. Only
                                                    ///< devices from the provided driver handle can be specified in this list.
    uint32_t* pNumDeviceEvents,                     ///< [in,out] Will contain the actual number of devices in phDevices that
                                                    ///< generated events. If non-zero, check pEvents to determine the devices
                                                    ///< and events that were received.
    zes_event_type_flags_t* pEvents                 ///< [in,out] An array that will continue the list of events for each
                                                    ///< device listened in phDevices.
                                                    ///< This array must be at least as big as count.
                                                    ///< For every device handle in phDevices, this will provide the events
                                                    ///< that occurred for that device at the same position in this array. If
                                                    ///< no event was received for a given device, the corresponding array
                                                    ///< entry will be zero.
    )
{
    auto pfnEventListen = ze_lib::context->zesDdiTable.Driver.pfnEventListen;
    if( nullptr == pfnEventListen )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEventListen( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Wait for events to be received from a one or more devices.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phDevices`
///         + `nullptr == pNumDeviceEvents`
///         + `nullptr == pEvents`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to listen to events.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or more of the supplied device handles belongs to a different driver.
ze_result_t ZE_APICALL
zesDriverEventListenEx(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint64_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then will check status and return immediately;
                                                    ///< if UINT64_MAX, then function will not return until events arrive.
    uint32_t count,                                 ///< [in] Number of device handles in phDevices.
    zes_device_handle_t* phDevices,                 ///< [in][range(0, count)] Device handles to listen to for events. Only
                                                    ///< devices from the provided driver handle can be specified in this list.
    uint32_t* pNumDeviceEvents,                     ///< [in,out] Will contain the actual number of devices in phDevices that
                                                    ///< generated events. If non-zero, check pEvents to determine the devices
                                                    ///< and events that were received.
    zes_event_type_flags_t* pEvents                 ///< [in,out] An array that will continue the list of events for each
                                                    ///< device listened in phDevices.
                                                    ///< This array must be at least as big as count.
                                                    ///< For every device handle in phDevices, this will provide the events
                                                    ///< that occurred for that device at the same position in this array. If
                                                    ///< no event was received for a given device, the corresponding array
                                                    ///< entry will be zero.
    )
{
    auto pfnEventListenEx = ze_lib::context->zesDdiTable.Driver.pfnEventListenEx;
    if( nullptr == pfnEventListenEx )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEventListenEx( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of Fabric ports in a device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumFabricPorts(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_fabric_port_handle_t* phPort                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumFabricPorts = ze_lib::context->zesDdiTable.Device.pfnEnumFabricPorts;
    if( nullptr == pfnEnumFabricPorts )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumFabricPorts( hDevice, pCount, phPort );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesFabricPortGetProperties(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.FabricPort.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPort, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port link type
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLinkType`
ze_result_t ZE_APICALL
zesFabricPortGetLinkType(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                    ///< port.
    )
{
    auto pfnGetLinkType = ze_lib::context->zesDdiTable.FabricPort.pfnGetLinkType;
    if( nullptr == pfnGetLinkType )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetLinkType( hPort, pLinkType );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t ZE_APICALL
zesFabricPortGetConfig(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
    )
{
    auto pfnGetConfig = ze_lib::context->zesDdiTable.FabricPort.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hPort, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set Fabric port configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFabricPortSetConfig(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
    )
{
    auto pfnSetConfig = ze_lib::context->zesDdiTable.FabricPort.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hPort, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port state - status (health/degraded/failed/disabled),
///        reasons for link degradation or instability, current rx/tx speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesFabricPortGetState(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
    )
{
    auto pfnGetState = ze_lib::context->zesDdiTable.FabricPort.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hPort, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port throughput
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThroughput`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t ZE_APICALL
zesFabricPortGetThroughput(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
    )
{
    auto pfnGetThroughput = ze_lib::context->zesDdiTable.FabricPort.pfnGetThroughput;
    if( nullptr == pfnGetThroughput )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetThroughput( hPort, pThroughput );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of fans
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumFans(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_fan_handle_t* phFan                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumFans = ze_lib::context->zesDdiTable.Device.pfnEnumFans;
    if( nullptr == pfnEnumFans )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumFans( hDevice, pCount, phFan );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesFanGetProperties(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Fan.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hFan, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan configurations and the current fan speed mode (default, fixed,
///        temp-speed table)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t ZE_APICALL
zesFanGetConfig(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
    )
{
    auto pfnGetConfig = ze_lib::context->zesDdiTable.Fan.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hFan, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Configure the fan to run with hardware factory settings (set mode to
///        ::ZES_FAN_SPEED_MODE_DEFAULT)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFanSetDefaultMode(
    zes_fan_handle_t hFan                           ///< [in] Handle for the component.
    )
{
    auto pfnSetDefaultMode = ze_lib::context->zesDdiTable.Fan.pfnSetDefaultMode;
    if( nullptr == pfnSetDefaultMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetDefaultMode( hFan );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Configure the fan to rotate at a fixed speed (set mode to
///        ::ZES_FAN_SPEED_MODE_FIXED)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == speed`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Fixing the fan speed not supported by the hardware or the fan speed units are not supported. See ::zes_fan_properties_t.supportedModes and ::zes_fan_properties_t.supportedUnits.
ze_result_t ZE_APICALL
zesFanSetFixedSpeedMode(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    const zes_fan_speed_t* speed                    ///< [in] The fixed fan speed setting
    )
{
    auto pfnSetFixedSpeedMode = ze_lib::context->zesDdiTable.Fan.pfnSetFixedSpeedMode;
    if( nullptr == pfnSetFixedSpeedMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetFixedSpeedMode( hFan, speed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Configure the fan to adjust speed based on a temperature/speed table
///        (set mode to ::ZES_FAN_SPEED_MODE_TABLE)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == speedTable`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The temperature/speed pairs in the array are not sorted on temperature from lowest to highest.
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Fan speed table not supported by the hardware or the fan speed units are not supported. See ::zes_fan_properties_t.supportedModes and ::zes_fan_properties_t.supportedUnits.
ze_result_t ZE_APICALL
zesFanSetSpeedTableMode(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    const zes_fan_speed_table_t* speedTable         ///< [in] A table containing temperature/speed pairs.
    )
{
    auto pfnSetSpeedTableMode = ze_lib::context->zesDdiTable.Fan.pfnSetSpeedTableMode;
    if( nullptr == pfnSetSpeedTableMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetSpeedTableMode( hFan, speedTable );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a fan - current mode and speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_FAN_SPEED_UNITS_PERCENT < units`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSpeed`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + The requested fan speed units are not supported. See ::zes_fan_properties_t.supportedUnits.
ze_result_t ZE_APICALL
zesFanGetState(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    zes_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
    int32_t* pSpeed                                 ///< [in,out] Will contain the current speed of the fan in the units
                                                    ///< requested. A value of -1 indicates that the fan speed cannot be
                                                    ///< measured.
    )
{
    auto pfnGetState = ze_lib::context->zesDdiTable.Fan.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hFan, units, pSpeed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of firmwares
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumFirmwares(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_firmware_handle_t* phFirmware               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumFirmwares = ze_lib::context->zesDdiTable.Device.pfnEnumFirmwares;
    if( nullptr == pfnEnumFirmwares )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumFirmwares( hDevice, pCount, phFirmware );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get firmware properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesFirmwareGetProperties(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    zes_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                    ///< firmware
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Firmware.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hFirmware, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Flash a new firmware image
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pImage`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
ze_result_t ZE_APICALL
zesFirmwareFlash(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    void* pImage,                                   ///< [in] Image of the new firmware to flash.
    uint32_t size                                   ///< [in] Size of the flash image.
    )
{
    auto pfnFlash = ze_lib::context->zesDdiTable.Firmware.pfnFlash;
    if( nullptr == pfnFlash )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFlash( hFirmware, pImage, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of frequency domains
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumFrequencyDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_freq_handle_t* phFrequency                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumFrequencyDomains = ze_lib::context->zesDdiTable.Device.pfnEnumFrequencyDomains;
    if( nullptr == pfnEnumFrequencyDomains )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency properties - available frequencies
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesFrequencyGetProperties(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Frequency.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hFrequency, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get available non-overclocked hardware clock frequencies for the
///        frequency domain
/// 
/// @details
///     - The list of available frequencies is returned in order of slowest to
///       fastest.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesFrequencyGetAvailableClocks(
    zes_freq_handle_t hFrequency,                   ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of frequencies that are available.
                                                    ///< if count is greater than the number of frequencies that are available,
                                                    ///< then the driver shall update the value with the correct number of frequencies.
    double* phFrequency                             ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                    ///< MHz and sorted from slowest to fastest.
                                                    ///< if count is less than the number of frequencies that are available,
                                                    ///< then the driver shall only retrieve that number of frequencies.
    )
{
    auto pfnGetAvailableClocks = ze_lib::context->zesDdiTable.Frequency.pfnGetAvailableClocks;
    if( nullptr == pfnGetAvailableClocks )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLimits`
ze_result_t ZE_APICALL
zesFrequencyGetRange(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                    ///< specified domain.
    )
{
    auto pfnGetRange = ze_lib::context->zesDdiTable.Frequency.pfnGetRange;
    if( nullptr == pfnGetRange )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetRange( hFrequency, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set frequency range between which the hardware can operate.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLimits`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencySetRange(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    const zes_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                    ///< specified domain.
    )
{
    auto pfnSetRange = ze_lib::context->zesDdiTable.Frequency.pfnSetRange;
    if( nullptr == pfnSetRange )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetRange( hFrequency, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency state - frequency request, actual frequency, TDP
///        limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesFrequencyGetState(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
    )
{
    auto pfnGetState = ze_lib::context->zesDdiTable.Frequency.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hFrequency, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency throttle time
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThrottleTime`
ze_result_t ZE_APICALL
zesFrequencyGetThrottleTime(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                    ///< specified domain.
    )
{
    auto pfnGetThrottleTime = ze_lib::context->zesDdiTable.Frequency.pfnGetThrottleTime;
    if( nullptr == pfnGetThrottleTime )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetThrottleTime( hFrequency, pThrottleTime );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the overclocking capabilities.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcCapabilities`
ze_result_t ZE_APICALL
zesFrequencyOcGetCapabilities(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure
                                                    ///< ::zes_oc_capabilities_t.
    )
{
    auto pfnOcGetCapabilities = ze_lib::context->zesDdiTable.Frequency.pfnOcGetCapabilities;
    if( nullptr == pfnOcGetCapabilities )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetCapabilities( hFrequency, pOcCapabilities );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current overclocking frequency target, if extended moded is
///        supported, will returned in 1 Mhz granularity.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCurrentOcFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see ::zes_oc_capabilities_t.maxOcFrequency, ::zes_oc_capabilities_t.maxOcVoltage, ::zes_oc_capabilities_t.minOcVoltageOffset, ::zes_oc_capabilities_t.maxOcVoltageOffset).
///         + Requested voltage overclock is very high but ::zes_oc_capabilities_t.isHighVoltModeEnabled is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcGetFrequencyTarget(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pCurrentOcFrequency                     ///< [out] Overclocking Frequency in MHz, if extended moded is supported,
                                                    ///< will returned in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                    ///< cannot be greater than ::zes_oc_capabilities_t.maxOcFrequency.
    )
{
    auto pfnOcGetFrequencyTarget = ze_lib::context->zesDdiTable.Frequency.pfnOcGetFrequencyTarget;
    if( nullptr == pfnOcGetFrequencyTarget )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetFrequencyTarget( hFrequency, pCurrentOcFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the current overclocking frequency target, if extended moded is
///        supported, can be set in 1 Mhz granularity.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see ::zes_oc_capabilities_t.maxOcFrequency, ::zes_oc_capabilities_t.maxOcVoltage, ::zes_oc_capabilities_t.minOcVoltageOffset, ::zes_oc_capabilities_t.maxOcVoltageOffset).
///         + Requested voltage overclock is very high but ::zes_oc_capabilities_t.isHighVoltModeEnabled is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetFrequencyTarget(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double CurrentOcFrequency                       ///< [in] Overclocking Frequency in MHz, if extended moded is supported, it
                                                    ///< could be set in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                    ///< cannot be greater than ::zes_oc_capabilities_t.maxOcFrequency.
    )
{
    auto pfnOcSetFrequencyTarget = ze_lib::context->zesDdiTable.Frequency.pfnOcSetFrequencyTarget;
    if( nullptr == pfnOcSetFrequencyTarget )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetFrequencyTarget( hFrequency, CurrentOcFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current overclocking voltage settings.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCurrentVoltageTarget`
///         + `nullptr == pCurrentVoltageOffset`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see ::zes_oc_capabilities_t.maxOcFrequency, ::zes_oc_capabilities_t.maxOcVoltage, ::zes_oc_capabilities_t.minOcVoltageOffset, ::zes_oc_capabilities_t.maxOcVoltageOffset).
///         + Requested voltage overclock is very high but ::zes_oc_capabilities_t.isHighVoltModeEnabled is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcGetVoltageTarget(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pCurrentVoltageTarget,                  ///< [out] Overclock voltage in Volts. This cannot be greater than
                                                    ///< ::zes_oc_capabilities_t.maxOcVoltage.
    double* pCurrentVoltageOffset                   ///< [out] This voltage offset is applied to all points on the
                                                    ///< voltage/frequency curve, include the new overclock voltageTarget. It
                                                    ///< can be in the range (::zes_oc_capabilities_t.minOcVoltageOffset,
                                                    ///< ::zes_oc_capabilities_t.maxOcVoltageOffset).
    )
{
    auto pfnOcGetVoltageTarget = ze_lib::context->zesDdiTable.Frequency.pfnOcGetVoltageTarget;
    if( nullptr == pfnOcGetVoltageTarget )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetVoltageTarget( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the current overclocking voltage settings.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see ::zes_oc_capabilities_t.maxOcFrequency, ::zes_oc_capabilities_t.maxOcVoltage, ::zes_oc_capabilities_t.minOcVoltageOffset, ::zes_oc_capabilities_t.maxOcVoltageOffset).
///         + Requested voltage overclock is very high but ::zes_oc_capabilities_t.isHighVoltModeEnabled is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetVoltageTarget(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double CurrentVoltageTarget,                    ///< [in] Overclock voltage in Volts. This cannot be greater than
                                                    ///< ::zes_oc_capabilities_t.maxOcVoltage.
    double CurrentVoltageOffset                     ///< [in] This voltage offset is applied to all points on the
                                                    ///< voltage/frequency curve, include the new overclock voltageTarget. It
                                                    ///< can be in the range (::zes_oc_capabilities_t.minOcVoltageOffset,
                                                    ///< ::zes_oc_capabilities_t.maxOcVoltageOffset).
    )
{
    auto pfnOcSetVoltageTarget = ze_lib::context->zesDdiTable.Frequency.pfnOcSetVoltageTarget;
    if( nullptr == pfnOcSetVoltageTarget )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetVoltageTarget( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the current overclocking mode.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OC_MODE_FIXED < CurrentOcMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see ::zes_oc_capabilities_t.maxOcFrequency, ::zes_oc_capabilities_t.maxOcVoltage, ::zes_oc_capabilities_t.minOcVoltageOffset, ::zes_oc_capabilities_t.maxOcVoltageOffset).
///         + Requested voltage overclock is very high but ::zes_oc_capabilities_t.isHighVoltModeEnabled is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetMode(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_oc_mode_t CurrentOcMode                     ///< [in] Current Overclocking Mode ::zes_oc_mode_t.
    )
{
    auto pfnOcSetMode = ze_lib::context->zesDdiTable.Frequency.pfnOcSetMode;
    if( nullptr == pfnOcSetMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetMode( hFrequency, CurrentOcMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current overclocking mode.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCurrentOcMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see ::zes_oc_capabilities_t.maxOcFrequency, ::zes_oc_capabilities_t.maxOcVoltage, ::zes_oc_capabilities_t.minOcVoltageOffset, ::zes_oc_capabilities_t.maxOcVoltageOffset).
///         + Requested voltage overclock is very high but ::zes_oc_capabilities_t.isHighVoltModeEnabled is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcGetMode(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_oc_mode_t* pCurrentOcMode                   ///< [out] Current Overclocking Mode ::zes_oc_mode_t.
    )
{
    auto pfnOcGetMode = ze_lib::context->zesDdiTable.Frequency.pfnOcGetMode;
    if( nullptr == pfnOcGetMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetMode( hFrequency, pCurrentOcMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the maximum current limit setting.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcIccMax`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + Capability ::zes_oc_capabilities_t.isIccMaxSupported is false for this frequency domain
ze_result_t ZE_APICALL
zesFrequencyOcGetIccMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                    ///< successful return.
    )
{
    auto pfnOcGetIccMax = ze_lib::context->zesDdiTable.Frequency.pfnOcGetIccMax;
    if( nullptr == pfnOcGetIccMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetIccMax( hFrequency, pOcIccMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the maximum current limit setting.
/// 
/// @details
///     - Setting ocIccMax to 0.0 will return the value to the factory default.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + Capability ::zes_oc_capabilities_t.isIccMaxSupported is false for this frequency domain
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified current limit is too low or too high
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetIccMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
    )
{
    auto pfnOcSetIccMax = ze_lib::context->zesDdiTable.Frequency.pfnOcSetIccMax;
    if( nullptr == pfnOcSetIccMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetIccMax( hFrequency, ocIccMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the maximum temperature limit setting.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcTjMax`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
ze_result_t ZE_APICALL
zesFrequencyOcGetTjMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                    ///< on successful return.
    )
{
    auto pfnOcGetTjMax = ze_lib::context->zesDdiTable.Frequency.pfnOcGetTjMax;
    if( nullptr == pfnOcGetTjMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetTjMax( hFrequency, pOcTjMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the maximum temperature limit setting.
/// 
/// @details
///     - Setting ocTjMax to 0.0 will return the value to the factory default.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + Capability ::zes_oc_capabilities_t.isTjMaxSupported is false for this frequency domain
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified temperature limit is too high
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetTjMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
    )
{
    auto pfnOcSetTjMax = ze_lib::context->zesDdiTable.Frequency.pfnOcSetTjMax;
    if( nullptr == pfnOcSetTjMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetTjMax( hFrequency, ocTjMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of LEDs
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumLeds(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_led_handle_t* phLed                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumLeds = ze_lib::context->zesDdiTable.Device.pfnEnumLeds;
    if( nullptr == pfnEnumLeds )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumLeds( hDevice, pCount, phLed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get LED properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesLedGetProperties(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Led.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hLed, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a LED - on/off, color
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesLedGetState(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
    )
{
    auto pfnGetState = ze_lib::context->zesDdiTable.Led.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hLed, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Turn the LED on/off
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesLedSetState(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    ze_bool_t enable                                ///< [in] Set to TRUE to turn the LED on, FALSE to turn off.
    )
{
    auto pfnSetState = ze_lib::context->zesDdiTable.Led.pfnSetState;
    if( nullptr == pfnSetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetState( hLed, enable );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the color of the LED
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pColor`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This LED doesn't not support color changes. See ::zes_led_properties_t.haveRGB.
ze_result_t ZE_APICALL
zesLedSetColor(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    const zes_led_color_t* pColor                   ///< [in] New color of the LED.
    )
{
    auto pfnSetColor = ze_lib::context->zesDdiTable.Led.pfnSetColor;
    if( nullptr == pfnSetColor )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetColor( hLed, pColor );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of memory modules
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumMemoryModules(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_mem_handle_t* phMemory                      ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumMemoryModules = ze_lib::context->zesDdiTable.Device.pfnEnumMemoryModules;
    if( nullptr == pfnEnumMemoryModules )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumMemoryModules( hDevice, pCount, phMemory );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesMemoryGetProperties(
    zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
    zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Memory.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hMemory, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory state - health, allocated
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesMemoryGetState(
    zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
    zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
    )
{
    auto pfnGetState = ze_lib::context->zesDdiTable.Memory.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hMemory, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory bandwidth
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pBandwidth`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t ZE_APICALL
zesMemoryGetBandwidth(
    zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
    zes_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the current health, free memory, total memory
                                                    ///< size.
    )
{
    auto pfnGetBandwidth = ze_lib::context->zesDdiTable.Memory.pfnGetBandwidth;
    if( nullptr == pfnGetBandwidth )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetBandwidth( hMemory, pBandwidth );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handles to accelerator domains whose performance can be optimized
///        via a Performance Factor
/// 
/// @details
///     - A Performance Factor should be tuned for each workload.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumPerformanceFactorDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_perf_handle_t* phPerf                       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumPerformanceFactorDomains = ze_lib::context->zesDdiTable.Device.pfnEnumPerformanceFactorDomains;
    if( nullptr == pfnEnumPerformanceFactorDomains )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties about a Performance Factor domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesPerformanceFactorGetProperties(
    zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
    zes_perf_properties_t* pProperties              ///< [in,out] Will contain information about the specified Performance
                                                    ///< Factor domain.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.PerformanceFactor.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPerf, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current Performance Factor for a given domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFactor`
ze_result_t ZE_APICALL
zesPerformanceFactorGetConfig(
    zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
    double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                    ///< hardware (may not be the same as the requested Performance Factor).
    )
{
    auto pfnGetConfig = ze_lib::context->zesDdiTable.PerformanceFactor.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hPerf, pFactor );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the performance factor for a domain
/// 
/// @details
///     - The Performance Factor is a number between 0 and 100.
///     - A Performance Factor is a hint to the hardware. Depending on the
///       hardware, the request may not be granted. Follow up this function with
///       a call to ::zesPerformanceFactorGetConfig() to determine the actual
///       factor being used by the hardware.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
ze_result_t ZE_APICALL
zesPerformanceFactorSetConfig(
    zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
    double factor                                   ///< [in] The new Performance Factor.
    )
{
    auto pfnSetConfig = ze_lib::context->zesDdiTable.PerformanceFactor.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hPerf, factor );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power domains
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumPowerDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_pwr_handle_t* phPower                       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumPowerDomains = ze_lib::context->zesDdiTable.Device.pfnEnumPowerDomains;
    if( nullptr == pfnEnumPowerDomains )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumPowerDomains( hDevice, pCount, phPower );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties related to a power domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesPowerGetProperties(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Power.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPower, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy counter
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pEnergy`
ze_result_t ZE_APICALL
zesPowerGetEnergyCounter(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                    ///< timestamp when the last counter value was measured.
    )
{
    auto pfnGetEnergyCounter = ze_lib::context->zesDdiTable.Power.pfnGetEnergyCounter;
    if( nullptr == pfnGetEnergyCounter )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetEnergyCounter( hPower, pEnergy );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
ze_result_t ZE_APICALL
zesPowerGetLimits(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit. If this is null, the
                                                    ///< current sustained power limits will not be returned.
    zes_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit. If this is null, the current
                                                    ///< peak power limits will not be returned.
    zes_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit. If this is null, the peak
                                                    ///< power limits will not be returned.
    )
{
    auto pfnGetLimits = ze_lib::context->zesDdiTable.Power.pfnGetLimits;
    if( nullptr == pfnGetLimits )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + The device is in use, meaning that the GPU is under Over clocking, applying power limits under overclocking is not supported.
ze_result_t ZE_APICALL
zesPowerSetLimits(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    const zes_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit. If this is null, no changes
                                                    ///< will be made to the sustained power limits.
    const zes_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit. If this is null, no changes will
                                                    ///< be made to the burst power limits.
    const zes_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit. If this is null, no changes will
                                                    ///< be made to the peak power limits.
    )
{
    auto pfnSetLimits = ze_lib::context->zesDdiTable.Power.pfnSetLimits;
    if( nullptr == pfnSetLimits )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy threshold
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThreshold`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Energy threshold not supported on this power domain (check ::zes_power_properties_t.isEnergyThresholdSupported).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
ze_result_t ZE_APICALL
zesPowerGetEnergyThreshold(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                    ///< enabled/energy threshold/process ID.
    )
{
    auto pfnGetEnergyThreshold = ze_lib::context->zesDdiTable.Power.pfnGetEnergyThreshold;
    if( nullptr == pfnGetEnergyThreshold )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetEnergyThreshold( hPower, pThreshold );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set energy threshold
/// 
/// @details
///     - An event ::ZES_EVENT_TYPE_FLAG_ENERGY_THRESHOLD_CROSSED will be
///       generated when the delta energy consumed starting from this call
///       exceeds the specified threshold. Use the function
///       ::zesDeviceEventRegister() to start receiving the event.
///     - Only one running process can control the energy threshold at a given
///       time. If another process attempts to change the energy threshold, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zesPowerGetEnergyThreshold() to determine the process ID currently
///       controlling this setting.
///     - Calling this function will remove any pending energy thresholds and
///       start counting from the time of this call.
///     - Once the energy threshold has been reached and the event generated,
///       the threshold is automatically removed. It is up to the application to
///       request a new threshold.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Energy threshold not supported on this power domain (check ::zes_power_properties_t.isEnergyThresholdSupported).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process has set the energy threshold.
ze_result_t ZE_APICALL
zesPowerSetEnergyThreshold(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    double threshold                                ///< [in] The energy threshold to be set in joules.
    )
{
    auto pfnSetEnergyThreshold = ze_lib::context->zesDdiTable.Power.pfnSetEnergyThreshold;
    if( nullptr == pfnSetEnergyThreshold )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetEnergyThreshold( hPower, threshold );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power supplies
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumPsus(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_psu_handle_t* phPsu                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumPsus = ze_lib::context->zesDdiTable.Device.pfnEnumPsus;
    if( nullptr == pfnEnumPsus )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumPsus( hDevice, pCount, phPsu );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power supply properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPsu`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesPsuGetProperties(
    zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
    zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Psu.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPsu, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current power supply state
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPsu`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesPsuGetState(
    zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
    zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
    )
{
    auto pfnGetState = ze_lib::context->zesDdiTable.Psu.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hPsu, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of all RAS error sets on a device
/// 
/// @details
///     - A RAS error set is a collection of RAS error counters of a given type
///       (correctable/uncorrectable) from hardware blocks contained within a
///       sub-device or within the device.
///     - A device without sub-devices will typically return two handles, one
///       for correctable errors sets and one for uncorrectable error sets.
///     - A device with sub-devices will return RAS error sets for each
///       sub-device and possibly RAS error sets for hardware blocks outside the
///       sub-devices.
///     - If the function completes successfully but pCount is set to 0, RAS
///       features are not available/enabled on this device.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumRasErrorSets(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_ras_handle_t* phRas                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumRasErrorSets = ze_lib::context->zesDdiTable.Device.pfnEnumRasErrorSets;
    if( nullptr == pfnEnumRasErrorSets )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumRasErrorSets( hDevice, pCount, phRas );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS properties of a given RAS error set - this enables discovery
///        of the type of RAS error set (correctable/uncorrectable) and if
///        located on a sub-device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesRasGetProperties(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Ras.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hRas, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the configured
///       threshold, the event ::ZES_EVENT_TYPE_FLAG_RAS_CORRECTABLE_ERRORS will
///       be triggered.
///     - When a particular RAS uncorrectable error counter exceeds the
///       configured threshold, the event
///       ::ZES_EVENT_TYPE_FLAG_RAS_UNCORRECTABLE_ERRORS will be triggered.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t ZE_APICALL
zesRasGetConfig(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    zes_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                    ///< thresholds used to trigger events
    )
{
    auto pfnGetConfig = ze_lib::context->zesDdiTable.Ras.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hRas, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the specified
///       threshold, the event ::ZES_EVENT_TYPE_FLAG_RAS_CORRECTABLE_ERRORS will
///       be generated.
///     - When a particular RAS uncorrectable error counter exceeds the
///       specified threshold, the event
///       ::ZES_EVENT_TYPE_FLAG_RAS_UNCORRECTABLE_ERRORS will be generated.
///     - Call ::zesRasGetState() and set the clear flag to true to restart
///       event generation once counters have exceeded thresholds.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to set thresholds.
ze_result_t ZE_APICALL
zesRasSetConfig(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
    )
{
    auto pfnSetConfig = ze_lib::context->zesDdiTable.Ras.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hRas, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current value of RAS error counters for a particular error set
/// 
/// @details
///     - Clearing errors will affect other threads/applications - the counter
///       values will start from zero.
///     - Clearing errors requires write permissions.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to clear error counters.
ze_result_t ZE_APICALL
zesRasGetState(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
    zes_ras_state_t* pState                         ///< [in,out] Breakdown of where errors have occurred
    )
{
    auto pfnGetState = ze_lib::context->zesDdiTable.Ras.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hRas, clear, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns handles to scheduler components.
/// 
/// @details
///     - Each scheduler component manages the distribution of work across one
///       or more accelerator engines.
///     - If an application wishes to change the scheduler behavior for all
///       accelerator engines of a specific type (e.g. compute), it should
///       select all the handles where the structure member
///       ::zes_sched_properties_t.engines contains that type.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumSchedulers(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_sched_handle_t* phScheduler                 ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumSchedulers = ze_lib::context->zesDdiTable.Device.pfnEnumSchedulers;
    if( nullptr == pfnEnumSchedulers )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumSchedulers( hDevice, pCount, phScheduler );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties related to a scheduler component
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesSchedulerGetProperties(
    zes_sched_handle_t hScheduler,                  ///< [in] Handle for the component.
    zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Scheduler.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hScheduler, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current scheduling mode in effect on a scheduler component.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t ZE_APICALL
zesSchedulerGetCurrentMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
    )
{
    auto pfnGetCurrentMode = ze_lib::context->zesDdiTable.Scheduler.pfnGetCurrentMode;
    if( nullptr == pfnGetCurrentMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetCurrentMode( hScheduler, pMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZES_SCHED_MODE_TIMEOUT
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t ZE_APICALL
zesSchedulerGetTimeoutModeProperties(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zes_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
    )
{
    auto pfnGetTimeoutModeProperties = ze_lib::context->zesDdiTable.Scheduler.pfnGetTimeoutModeProperties;
    if( nullptr == pfnGetTimeoutModeProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZES_SCHED_MODE_TIMESLICE
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t ZE_APICALL
zesSchedulerGetTimesliceModeProperties(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zes_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
    )
{
    auto pfnGetTimesliceModeProperties = ze_lib::context->zesDdiTable.Scheduler.pfnGetTimesliceModeProperties;
    if( nullptr == pfnGetTimesliceModeProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_TIMEOUT or update scheduler
///        mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized for multiple applications or contexts
///       submitting work to the hardware. When higher priority work arrives,
///       the scheduler attempts to pause the current executing work within some
///       timeout interval, then submits the other work.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t ZE_APICALL
zesSchedulerSetTimeoutMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    zes_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    auto pfnSetTimeoutMode = ze_lib::context->zesDdiTable.Scheduler.pfnSetTimeoutMode;
    if( nullptr == pfnSetTimeoutMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_TIMESLICE or update
///        scheduler mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized to provide fair sharing of hardware execution
///       time between multiple contexts submitting work to the hardware
///       concurrently.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t ZE_APICALL
zesSchedulerSetTimesliceMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    zes_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    auto pfnSetTimesliceMode = ze_lib::context->zesDdiTable.Scheduler.pfnSetTimesliceMode;
    if( nullptr == pfnSetTimesliceMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_EXCLUSIVE
/// 
/// @details
///     - This mode is optimized for single application/context use-cases. It
///       permits a context to run indefinitely on the hardware without being
///       preempted or terminated. All pending work for other contexts must wait
///       until the running context completes with no further submitted work.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t ZE_APICALL
zesSchedulerSetExclusiveMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    auto pfnSetExclusiveMode = ze_lib::context->zesDdiTable.Scheduler.pfnSetExclusiveMode;
    if( nullptr == pfnSetExclusiveMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetExclusiveMode( hScheduler, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_COMPUTE_UNIT_DEBUG
/// 
/// @details
///     - This is a special mode that must ben enabled when debugging an
///       application that uses this device e.g. using the Level0 Debug API.
///     - It ensures that only one command queue can execute work on the
///       hardware at a given time. Work is permitted to run as long as needed
///       without enforcing any scheduler fairness policies.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t ZE_APICALL
zesSchedulerSetComputeUnitDebugMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    auto pfnSetComputeUnitDebugMode = ze_lib::context->zesDdiTable.Scheduler.pfnSetComputeUnitDebugMode;
    if( nullptr == pfnSetComputeUnitDebugMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of standby controls
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumStandbyDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_standby_handle_t* phStandby                 ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumStandbyDomains = ze_lib::context->zesDdiTable.Device.pfnEnumStandbyDomains;
    if( nullptr == pfnEnumStandbyDomains )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumStandbyDomains( hDevice, pCount, phStandby );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get standby hardware component properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesStandbyGetProperties(
    zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
    zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Standby.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hStandby, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current standby promotion mode
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
ze_result_t ZE_APICALL
zesStandbyGetMode(
    zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
    zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
    )
{
    auto pfnGetMode = ze_lib::context->zesDdiTable.Standby.pfnGetMode;
    if( nullptr == pfnGetMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetMode( hStandby, pMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set standby promotion mode
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_STANDBY_PROMO_MODE_NEVER < mode`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesStandbySetMode(
    zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
    zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
    )
{
    auto pfnSetMode = ze_lib::context->zesDdiTable.Standby.pfnSetMode;
    if( nullptr == pfnSetMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetMode( hStandby, mode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of temperature sensors
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumTemperatureSensors(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_temp_handle_t* phTemperature                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    auto pfnEnumTemperatureSensors = ze_lib::context->zesDdiTable.Device.pfnEnumTemperatureSensors;
    if( nullptr == pfnEnumTemperatureSensors )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature sensor properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesTemperatureGetProperties(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
    )
{
    auto pfnGetProperties = ze_lib::context->zesDdiTable.Temperature.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hTemperature, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature configuration for this sensor - which events are
///        triggered and the trigger conditions
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Temperature thresholds are not supported on this temperature sensor. Generally this is only supported for temperature sensor ::ZES_TEMP_SENSORS_GLOBAL
///         + One or both of the thresholds is not supported - check ::zes_temp_properties_t.isThreshold1Supported and ::zes_temp_properties_t.isThreshold2Supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
ze_result_t ZE_APICALL
zesTemperatureGetConfig(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
    )
{
    auto pfnGetConfig = ze_lib::context->zesDdiTable.Temperature.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hTemperature, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set temperature configuration for this sensor - indicates which events
///        are triggered and the trigger conditions
/// 
/// @details
///     - Events ::ZES_EVENT_TYPE_FLAG_TEMP_CRITICAL will be triggered when
///       temperature reaches the critical range. Use the function
///       ::zesDeviceEventRegister() to start receiving this event.
///     - Events ::ZES_EVENT_TYPE_FLAG_TEMP_THRESHOLD1 and
///       ::ZES_EVENT_TYPE_FLAG_TEMP_THRESHOLD2 will be generated when
///       temperature cross the thresholds set using this function. Use the
///       function ::zesDeviceEventRegister() to start receiving these events.
///     - Only one running process can set the temperature configuration at a
///       time. If another process attempts to change the configuration, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zesTemperatureGetConfig() will return the process ID currently
///       controlling these settings.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Temperature thresholds are not supported on this temperature sensor. Generally they are only supported for temperature sensor ::ZES_TEMP_SENSORS_GLOBAL
///         + Enabling the critical temperature event is not supported - check ::zes_temp_properties_t.isCriticalTempSupported
///         + One or both of the thresholds is not supported - check ::zes_temp_properties_t.isThreshold1Supported and ::zes_temp_properties_t.isThreshold2Supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or both the thresholds is above TjMax (see ::zesFrequencyOcGetTjMax()). Temperature thresholds must be below this value.
ze_result_t ZE_APICALL
zesTemperatureSetConfig(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    const zes_temp_config_t* pConfig                ///< [in] New configuration.
    )
{
    auto pfnSetConfig = ze_lib::context->zesDdiTable.Temperature.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hTemperature, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the temperature from a specified sensor
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pTemperature`
ze_result_t ZE_APICALL
zesTemperatureGetState(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                    ///< in degrees Celsius.
    )
{
    auto pfnGetState = ze_lib::context->zesDdiTable.Temperature.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hTemperature, pTemperature );
}

} // extern "C"
