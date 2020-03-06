/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_cl_interop.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for OpenCL Interoperability
 *
 */
#include "ze_api.hpp"
#include "ze_singleton.h"

#define _STRING(s) #s
#define STRING(s) _STRING(s)

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
#if ZE_ENABLE_OCL_INTEROP
    /// @brief Registers OpenCL memory with 'One API'
    /// 
    /// @returns
    ///     - void*: pointer to device allocation
    /// 
    /// @throws result_t
    void* __zecall
    Device::RegisterCLMemory(
        cl_context context,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem                                      ///< [in] the OpenCL memory to register
        )
    {
        void* ptr;

        auto result = static_cast<result_t>( ::zeDeviceRegisterCLMemory(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            context,
            mem,
            &ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::RegisterCLMemory" );

        return ptr;
    }
#endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
#if ZE_ENABLE_OCL_INTEROP
    /// @brief Registers OpenCL program with 'One API'
    /// 
    /// @returns
    ///     - Module*: pointer to handle of module object created
    /// 
    /// @throws result_t
    Module* __zecall
    Device::RegisterCLProgram(
        cl_context context,                             ///< [in] the OpenCL context that created the program
        cl_program program                              ///< [in] the OpenCL program to register
        )
    {
        ze_module_handle_t hModule;

        auto result = static_cast<result_t>( ::zeDeviceRegisterCLProgram(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            context,
            program,
            &hModule ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::RegisterCLProgram" );

        Module* pModule = nullptr;

        try
        {
            pModule = new Module( reinterpret_cast<module_handle_t>( hModule ), this, m_desc );
        }
        catch( std::bad_alloc& )
        {
            delete pModule;
            pModule = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Device::RegisterCLProgram" );
        }

        return pModule;
    }
#endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
#if ZE_ENABLE_OCL_INTEROP
    /// @brief Registers OpenCL command queue with 'One API'
    /// 
    /// @returns
    ///     - CommandQueue*: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    CommandQueue* __zecall
    Device::RegisterCLCommandQueue(
        cl_context context,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue                  ///< [in] the OpenCL command queue to register
        )
    {
        ze_command_queue_handle_t hCommandQueue;

        auto result = static_cast<result_t>( ::zeDeviceRegisterCLCommandQueue(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            context,
            command_queue,
            &hCommandQueue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::RegisterCLCommandQueue" );

        CommandQueue* pCommandQueue = nullptr;

        try
        {
            pCommandQueue = new CommandQueue( reinterpret_cast<command_queue_handle_t>( hCommandQueue ), this, m_desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandQueue;
            pCommandQueue = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Device::RegisterCLCommandQueue" );
        }

        return pCommandQueue;
    }
#endif // ZE_ENABLE_OCL_INTEROP

} // namespace ze

namespace ze
{
} // namespace ze
