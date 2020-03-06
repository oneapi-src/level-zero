/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_module.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Module
 *
 */
#include "ze_api.hpp"
#include "ze_singleton.h"

#define _STRING(s) #s
#define STRING(s) _STRING(s)

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    Module::Module( 
        module_handle_t handle,                         ///< [in] handle of module object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the module object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    ModuleBuildLog::ModuleBuildLog( 
        module_build_log_handle_t handle,               ///< [in] handle of the buildlog object
        Module* pModule                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pModule( pModule )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Kernel::Kernel( 
        kernel_handle_t handle,                         ///< [in] handle of kernel object
        Module* pModule,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the kernel object
        ) :
        m_handle( handle ),
        m_pModule( pModule ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates module object from an input IL or native binary.
    /// 
    /// @details
    ///     - Compiles the module for execution on the device.
    ///     - The module can only be used on the device on which it was created.
    ///     - The module can be copied to other devices within the same driver
    ///       instance by using ::zeModuleGetNativeBinary.
    ///     - The following build options are supported:
    ///         + "-ze-opt-disable" - Disable optimizations
    ///         + "-ze-opt-greater-than-4GB-buffer-required" - Use 64-bit offset
    ///           calculations for buffers.
    ///         + "-ze-opt-large-register-file" - Increase number of registers
    ///           available to threads.
    ///     - A build log can optionally be returned to the caller. The caller is
    ///       responsible for destroying build log using ::zeModuleBuildLogDestroy.
    ///     - The module descriptor constants are only supported for SPIR-V
    ///       specialization constants.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - Module*: pointer to handle of module object created
    ///     - ModuleBuildLog*: pointer to handle of module's build log.
    /// 
    /// @throws result_t
    Module* __zecall
    Module::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc,                             ///< [in] pointer to module descriptor
        ModuleBuildLog** ppBuildLog                     ///< [out][optional] pointer to pointer to module's build log.
        )
    {
        ze_module_handle_t hModule;

        ze_module_build_log_handle_t hBuildLog;

        auto result = static_cast<result_t>( ::zeModuleCreate(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_module_desc_t*>( desc ),
            &hModule,
            ( ppBuildLog ) ? &hBuildLog : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Module::Create" );

        Module* pModule = nullptr;

        try
        {
            pModule = new Module( reinterpret_cast<module_handle_t>( hModule ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pModule;
            pModule = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Module::Create" );
        }

        if( ppBuildLog )
            *ppBuildLog =  nullptr;

        try
        {
            if( ppBuildLog )
                *ppBuildLog =  new ModuleBuildLog( reinterpret_cast<module_build_log_handle_t>( hBuildLog ), pModule );
        }
        catch( std::bad_alloc& )
        {
            if( ppBuildLog )
            {
                delete *ppBuildLog;
                *ppBuildLog =  nullptr;
            }
            delete pModule;
            pModule = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Module::Create" );
        }

        return pModule;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys module
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the module before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this module
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same module handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Module::Destroy(
        Module* pModule                                 ///< [in][release] pointer to the module
        )
    {
        auto result = static_cast<result_t>( ::zeModuleDestroy(
            reinterpret_cast<ze_module_handle_t>( pModule->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Module::Destroy" );

        delete pModule;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys module build log object
    /// 
    /// @details
    ///     - The implementation of this function will immediately free all Host
    ///       allocations associated with this object
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same build log handle.
    ///     - The implementation of this function should be lock-free.
    ///     - This function can be called before or after ::zeModuleDestroy for the
    ///       associated module.
    /// 
    /// @throws result_t
    void __zecall
    ModuleBuildLog::Destroy(
        ModuleBuildLog* pModuleBuildLog                 ///< [in][release] pointer to the module build log object.
        )
    {
        auto result = static_cast<result_t>( ::zeModuleBuildLogDestroy(
            reinterpret_cast<ze_module_build_log_handle_t>( pModuleBuildLog->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::ModuleBuildLog::Destroy" );

        delete pModuleBuildLog;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves text string for build log.
    /// 
    /// @details
    ///     - The caller can pass nullptr for pBuildLog when querying only for size.
    ///     - The caller must provide memory for build log.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    ModuleBuildLog::GetString(
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        auto result = static_cast<result_t>( ::zeModuleBuildLogGetString(
            reinterpret_cast<ze_module_build_log_handle_t>( getHandle() ),
            pSize,
            pBuildLog ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::ModuleBuildLog::GetString" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve native binary from Module.
    /// 
    /// @details
    ///     - The native binary output can be cached to disk and new modules can be
    ///       later constructed from the cached copy.
    ///     - The native binary will retain debugging information that is associated
    ///       with a module.
    ///     - The caller can pass nullptr for pModuleNativeBinary when querying only
    ///       for size.
    ///     - The implementation will copy the native binary into a buffer supplied
    ///       by the caller.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Module::GetNativeBinary(
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        auto result = static_cast<result_t>( ::zeModuleGetNativeBinary(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            pSize,
            pModuleNativeBinary ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Module::GetNativeBinary" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve global variable pointer from Module.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: device visible pointer
    /// 
    /// @throws result_t
    void* __zecall
    Module::GetGlobalPointer(
        const char* pGlobalName                         ///< [in] name of global variable in module
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeModuleGetGlobalPointer(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            pGlobalName,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Module::GetGlobalPointer" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve all kernel names in the module.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Module::GetKernelNames(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of names available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of names.
                                                        ///< if count is larger than the number of names available, then the driver
                                                        ///< will update the value with the correct number of names available.
        const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions
        )
    {
        auto result = static_cast<result_t>( ::zeModuleGetKernelNames(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            pCount,
            pNames ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Module::GetKernelNames" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Create a kernel object from a module by name
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - Kernel*: handle of the Function object
    /// 
    /// @throws result_t
    Kernel* __zecall
    Kernel::Create(
        Module* pModule,                                ///< [in] pointer to the module
        const desc_t* desc                              ///< [in] pointer to kernel descriptor
        )
    {
        ze_kernel_handle_t hKernel;

        auto result = static_cast<result_t>( ::zeKernelCreate(
            reinterpret_cast<ze_module_handle_t>( pModule->getHandle() ),
            reinterpret_cast<const ze_kernel_desc_t*>( desc ),
            &hKernel ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Kernel::Create" );

        Kernel* pKernel = nullptr;

        try
        {
            pKernel = new Kernel( reinterpret_cast<kernel_handle_t>( hKernel ), pModule, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pKernel;
            pKernel = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Kernel::Create" );
        }

        return pKernel;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a kernel object
    /// 
    /// @details
    ///     - All kernels must be destroyed before the module is destroyed.
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the kernel before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this kernel
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same kernel handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Kernel::Destroy(
        Kernel* pKernel                                 ///< [in][release] pointer to the kernel object
        )
    {
        auto result = static_cast<result_t>( ::zeKernelDestroy(
            reinterpret_cast<ze_kernel_handle_t>( pKernel->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Kernel::Destroy" );

        delete pKernel;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve a function pointer from a module by name
    /// 
    /// @details
    ///     - The function pointer is unique for the device on which the module was
    ///       created.
    ///     - The function pointer is no longer valid if module is destroyed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: pointer to function.
    /// 
    /// @throws result_t
    void* __zecall
    Module::GetFunctionPointer(
        const char* pFunctionName                       ///< [in] Name of function to retrieve function pointer for.
        )
    {
        void* pfnFunction;

        auto result = static_cast<result_t>( ::zeModuleGetFunctionPointer(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            pFunctionName,
            &pfnFunction ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Module::GetFunctionPointer" );

        return pfnFunction;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set group size for a kernel
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same kernel handle.
    ///     - The implementation of this function should be lock-free.
    ///     - The implementation will copy the group size information into a command
    ///       list when the function is appended.
    /// 
    /// @throws result_t
    void __zecall
    Kernel::SetGroupSize(
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
        )
    {
        auto result = static_cast<result_t>( ::zeKernelSetGroupSize(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            groupSizeX,
            groupSizeY,
            groupSizeZ ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Kernel::SetGroupSize" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query a suggested group size for a kernel given a global size for each
    ///        dimension.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - This function ignores the group size that is set using
    ///       ::zeKernelSetGroupSize.
    /// 
    /// @returns
    ///     - uint32_t: recommended size of group for X dimension
    ///     - uint32_t: recommended size of group for Y dimension
    ///     - uint32_t: recommended size of group for Z dimension
    /// 
    /// @throws result_t
    std::tuple<uint32_t, uint32_t, uint32_t> __zecall
    Kernel::SuggestGroupSize(
        uint32_t globalSizeX,                           ///< [in] global width for X dimension
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension
        uint32_t globalSizeZ                            ///< [in] global width for Z dimension
        )
    {
        uint32_t groupSizeX;

        uint32_t groupSizeY;

        uint32_t groupSizeZ;

        auto result = static_cast<result_t>( ::zeKernelSuggestGroupSize(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            globalSizeX,
            globalSizeY,
            globalSizeZ,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Kernel::SuggestGroupSize" );

        return std::make_tuple( groupSizeX, groupSizeY, groupSizeZ );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query a suggested max group count a cooperative kernel.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - uint32_t: recommended total group count.
    /// 
    /// @throws result_t
    uint32_t __zecall
    Kernel::SuggestMaxCooperativeGroupCount(
        void
        )
    {
        uint32_t totalGroupCount;

        auto result = static_cast<result_t>( ::zeKernelSuggestMaxCooperativeGroupCount(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            &totalGroupCount ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Kernel::SuggestMaxCooperativeGroupCount" );

        return totalGroupCount;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set kernel argument used on kernel launch.
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    ///     - The implementation will copy the arguments into a command list when
    ///       the function is appended.
    /// 
    /// @throws result_t
    void __zecall
    Kernel::SetArgumentValue(
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelSetArgumentValue(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            argIndex,
            argSize,
            pArgValue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Kernel::SetArgumentValue" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets a kernel attribute
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clSetKernelExecInfo**
    /// 
    /// @throws result_t
    void __zecall
    Kernel::SetAttribute(
        attribute_t attr,                               ///< [in] attribute to set
        uint32_t size,                                  ///< [in] size in bytes of kernel attribute value.
        const void* pValue                              ///< [in][optional] pointer to attribute value.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelSetAttribute(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            static_cast<ze_kernel_attribute_t>( attr ),
            size,
            pValue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Kernel::SetAttribute" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Gets a kernel attribute
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    ///     - The caller sets pValue to nullptr when querying only for size.
    ///     - The caller must provide memory for pValue querying when querying size.
    /// 
    /// @throws result_t
    void __zecall
    Kernel::GetAttribute(
        attribute_t attr,                               ///< [in] attribute to get. Documentation for ::ze_kernel_attribute_t for
                                                        ///< return type information for pValue.
        uint32_t* pSize,                                ///< [in,out] size in bytes needed for kernel attribute value. If pValue is
                                                        ///< nullptr then the size needed for pValue memory will be written to
                                                        ///< pSize. Only need to query size for arbitrary sized attributes.
        void* pValue                                    ///< [in,out][optional] pointer to attribute value result.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelGetAttribute(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            static_cast<ze_kernel_attribute_t>( attr ),
            pSize,
            pValue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Kernel::GetAttribute" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the preferred Intermediate cache configuration for a kernel.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same kernel handle.
    /// 
    /// @throws result_t
    void __zecall
    Kernel::SetIntermediateCacheConfig(
        Device::cache_config_t CacheConfig              ///< [in] CacheConfig
        )
    {
        auto result = static_cast<result_t>( ::zeKernelSetIntermediateCacheConfig(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            static_cast<ze_cache_config_t>( CacheConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Kernel::SetIntermediateCacheConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve kernel properties.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Kernel::GetProperties(
        properties_t* pKernelProperties                 ///< [in,out] query result for kernel properties.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelGetProperties(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_properties_t*>( pKernelProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Kernel::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch kernel over one or more work groups.
    /// 
    /// @details
    ///     - This may **only** be called for a command list created with command
    ///       queue group ordinal that supports compute.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendLaunchKernel(
        Kernel* pKernel,                                ///< [in] pointer to the kernel object
        const group_count_t* pLaunchFuncArgs,           ///< [in] thread group launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendLaunchKernel(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_handle_t>( pKernel->getHandle() ),
            reinterpret_cast<const ze_group_count_t*>( pLaunchFuncArgs ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendLaunchKernel" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch kernel cooperatively over one or more work groups.
    /// 
    /// @details
    ///     - This may **only** be called for a command list created with command
    ///       queue group ordinal that supports compute.
    ///     - This may only be used for a command list that are submitted to command
    ///       queue with cooperative flag set.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    ///     - Use ::zeKernelSuggestMaxCooperativeGroupCount to recommend max group
    ///       count for device for cooperative functions that device supports.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendLaunchCooperativeKernel(
        Kernel* pKernel,                                ///< [in] pointer to the kernel object
        const group_count_t* pLaunchFuncArgs,           ///< [in] thread group launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendLaunchCooperativeKernel(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_handle_t>( pKernel->getHandle() ),
            reinterpret_cast<const ze_group_count_t*>( pLaunchFuncArgs ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendLaunchCooperativeKernel" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch kernel over one or more work groups using indirect arguments.
    /// 
    /// @details
    ///     - The launch arguments need to be device visible.
    ///     - The launch arguments buffer may not be reused until the function has
    ///       completed on the device.
    ///     - This may **only** be called for a command list created with command
    ///       queue group ordinal that supports compute.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendLaunchKernelIndirect(
        Kernel* pKernel,                                ///< [in] pointer to the kernel object
        const group_count_t* pLaunchArgumentsBuffer,    ///< [in] pointer to device buffer that will contain thread group launch
                                                        ///< arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendLaunchKernelIndirect(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_handle_t>( pKernel->getHandle() ),
            reinterpret_cast<const ze_group_count_t*>( pLaunchArgumentsBuffer ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendLaunchKernelIndirect" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch multiple kernels over one or more work groups using an array of
    ///        indirect arguments.
    /// 
    /// @details
    ///     - The array of launch arguments need to be device visible.
    ///     - The array of launch arguments buffer may not be reused until the
    ///       kernel has completed on the device.
    ///     - This may **only** be called for a command list created with command
    ///       queue group ordinal that supports compute.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendLaunchMultipleKernelsIndirect(
        uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
        Kernel** ppKernels,                             ///< [in][range(0, numKernels)] handles of the kernel objects
        const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of kernels to launch; value must be less-than or equal-to
                                                        ///< numKernels
        const group_count_t* pLaunchArgumentsBuffer,    ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                        ///< a contiguous array of thread group launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_kernel_handle_t> hKernels;
        hKernels.resize( 0 );
        hKernels.reserve( numKernels );
        for( uint32_t i = 0; i < numKernels; ++i )
            hKernels.emplace_back( reinterpret_cast<ze_kernel_handle_t>( ppKernels[ i ]->getHandle() ) );

        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendLaunchMultipleKernelsIndirect(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            numKernels,
            hKernels.data(),
            pCountBuffer,
            reinterpret_cast<const ze_group_count_t*>( pLaunchArgumentsBuffer ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendLaunchMultipleKernelsIndirect" );
    }

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_version_t to std::string
    std::string to_string( const Module::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Module::desc_version_t::CURRENT:
            str = "Module::desc_version_t::CURRENT";
            break;

        default:
            str = "Module::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::format_t to std::string
    std::string to_string( const Module::format_t val )
    {
        std::string str;

        switch( val )
        {
        case Module::format_t::IL_SPIRV:
            str = "Module::format_t::IL_SPIRV";
            break;

        case Module::format_t::NATIVE:
            str = "Module::format_t::NATIVE";
            break;

        default:
            str = "Module::format_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::constants_t to std::string
    std::string to_string( const Module::constants_t val )
    {
        std::string str;
        
        str += "Module::constants_t::numConstants : ";
        str += std::to_string(val.numConstants);
        str += "\n";
        
        str += "Module::constants_t::pConstantIds : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pConstantIds);
            str += ss.str();
        }
        str += "\n";
        
        str += "Module::constants_t::pConstantValues : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pConstantValues);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_t to std::string
    std::string to_string( const Module::desc_t val )
    {
        std::string str;
        
        str += "Module::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Module::desc_t::format : ";
        str += to_string(val.format);
        str += "\n";
        
        str += "Module::desc_t::inputSize : ";
        str += std::to_string(val.inputSize);
        str += "\n";
        
        str += "Module::desc_t::pInputModule : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pInputModule);
            str += ss.str();
        }
        str += "\n";
        
        str += "Module::desc_t::pBuildFlags : ";
        str += val.pBuildFlags;
        str += "\n";
        
        str += "Module::desc_t::pConstants : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pConstants);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_version_t to std::string
    std::string to_string( const Kernel::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::desc_version_t::CURRENT:
            str = "Kernel::desc_version_t::CURRENT";
            break;

        default:
            str = "Kernel::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::flag_t to std::string
    std::string to_string( const Kernel::flag_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::flag_t::NONE:
            str = "Kernel::flag_t::NONE";
            break;

        case Kernel::flag_t::FORCE_RESIDENCY:
            str = "Kernel::flag_t::FORCE_RESIDENCY";
            break;

        default:
            str = "Kernel::flag_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::attribute_t to std::string
    std::string to_string( const Kernel::attribute_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::attribute_t::KERNEL_ATTR_INDIRECT_HOST_ACCESS:
            str = "Kernel::attribute_t::KERNEL_ATTR_INDIRECT_HOST_ACCESS";
            break;

        case Kernel::attribute_t::KERNEL_ATTR_INDIRECT_DEVICE_ACCESS:
            str = "Kernel::attribute_t::KERNEL_ATTR_INDIRECT_DEVICE_ACCESS";
            break;

        case Kernel::attribute_t::KERNEL_ATTR_INDIRECT_SHARED_ACCESS:
            str = "Kernel::attribute_t::KERNEL_ATTR_INDIRECT_SHARED_ACCESS";
            break;

        case Kernel::attribute_t::KERNEL_ATTR_SOURCE_ATTRIBUTE:
            str = "Kernel::attribute_t::KERNEL_ATTR_SOURCE_ATTRIBUTE";
            break;

        default:
            str = "Kernel::attribute_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::properties_version_t to std::string
    std::string to_string( const Kernel::properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::properties_version_t::CURRENT:
            str = "Kernel::properties_version_t::CURRENT";
            break;

        default:
            str = "Kernel::properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_t to std::string
    std::string to_string( const Kernel::desc_t val )
    {
        std::string str;
        
        str += "Kernel::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Kernel::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Kernel::desc_t::pKernelName : ";
        str += val.pKernelName;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::properties_t to std::string
    std::string to_string( const Kernel::properties_t val )
    {
        std::string str;
        
        str += "Kernel::properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Kernel::properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "Kernel::properties_t::numKernelArgs : ";
        str += std::to_string(val.numKernelArgs);
        str += "\n";
        
        str += "Kernel::properties_t::requiredGroupSizeX : ";
        str += std::to_string(val.requiredGroupSizeX);
        str += "\n";
        
        str += "Kernel::properties_t::requiredGroupSizeY : ";
        str += std::to_string(val.requiredGroupSizeY);
        str += "\n";
        
        str += "Kernel::properties_t::requiredGroupSizeZ : ";
        str += std::to_string(val.requiredGroupSizeZ);
        str += "\n";

        return str;
    }

} // namespace ze
