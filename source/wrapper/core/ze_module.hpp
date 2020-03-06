/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_module.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Module
 *
 */
#ifndef _ZE_MODULE_HPP
#define _ZE_MODULE_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_KERNEL_NAME
/// @brief Maximum device name string size
#define ZE_MAX_KERNEL_NAME  256
#endif // ZE_MAX_KERNEL_NAME

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for module
    class Module
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_module_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported module creation input formats
        enum class format_t
        {
            IL_SPIRV = 0,                                   ///< Format is SPIRV IL format
            NATIVE,                                         ///< Format is device native format

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Specialization constants - User defined constants
        struct constants_t
        {
            uint32_t numConstants;                          ///< [in] Number of specialization constants.
            const uint32_t* pConstantIds;                   ///< [in] Pointer to array of IDs that is sized to numConstants.
            const uint64_t* pConstantValues;                ///< [in] Pointer to array of values that is sized to numConstants.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Module descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_MODULE_DESC_VERSION_CURRENT
            format_t format;                                ///< [in] Module format passed in with pInputModule
            size_t inputSize = 0;                           ///< [in] size of input IL or ISA from pInputModule.
            const uint8_t* pInputModule = nullptr;          ///< [in] pointer to IL or ISA
            const char* pBuildFlags = nullptr;              ///< [in] string containing compiler flags. See programming guide for build
                                                            ///< flags.
            const constants_t* pConstants = nullptr;        ///< [in] pointer to specialization constants. Valid only for SPIR-V input.
                                                            ///< This must be set to nullptr if no specialization constants are
                                                            ///< provided.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        module_handle_t m_handle;                       ///< [in] handle of module object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the module object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Module( void ) = delete;
        Module( 
            module_handle_t handle,                         ///< [in] handle of module object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the module object
            );

        ~Module( void ) = default;

        Module( Module const& other ) = delete;
        void operator=( Module const& other ) = delete;

        Module( Module&& other ) = delete;
        void operator=( Module&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - Module*: pointer to handle of module object created
        ///     - ModuleBuildLog*: pointer to handle of module's build log.
        /// 
        /// @throws result_t
        static Module* __zecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc,                             ///< [in] pointer to module descriptor
            ModuleBuildLog** ppBuildLog = nullptr           ///< [out][optional] pointer to pointer to module's build log.
            );

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
        /// @throws result_t
        static void __zecall
        Destroy(
            Module* pModule                                 ///< [in][release] pointer to the module
            );

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
        /// @throws result_t
        void __zecall
        GetNativeBinary(
            size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
            uint8_t* pModuleNativeBinary = nullptr          ///< [in,out][optional] byte pointer to native binary
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve global variable pointer from Module.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - void*: device visible pointer
        /// 
        /// @throws result_t
        void* __zecall
        GetGlobalPointer(
            const char* pGlobalName                         ///< [in] name of global variable in module
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve all kernel names in the module.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetKernelNames(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of names available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of names.
                                                            ///< if count is larger than the number of names available, then the driver
                                                            ///< will update the value with the correct number of names available.
            const char** pNames = nullptr                   ///< [in,out][optional][range(0, *pCount)] array of names of functions
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve a function pointer from a module by name
        /// 
        /// @details
        ///     - The function pointer is unique for the device on which the module was
        ///       created.
        ///     - The function pointer is no longer valid if module is destroyed.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - void*: pointer to function.
        /// 
        /// @throws result_t
        void* __zecall
        GetFunctionPointer(
            const char* pFunctionName                       ///< [in] Name of function to retrieve function pointer for.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for buildlog
    class ModuleBuildLog
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////
        module_build_log_handle_t m_handle;             ///< [in] handle of the buildlog object
        Module* m_pModule;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        ModuleBuildLog( void ) = delete;
        ModuleBuildLog( 
            module_build_log_handle_t handle,               ///< [in] handle of the buildlog object
            Module* pModule                                 ///< [in] pointer to owner object
            );

        ~ModuleBuildLog( void ) = default;

        ModuleBuildLog( ModuleBuildLog const& other ) = delete;
        void operator=( ModuleBuildLog const& other ) = delete;

        ModuleBuildLog( ModuleBuildLog&& other ) = delete;
        void operator=( ModuleBuildLog&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getModule( void ) const { return m_pModule; }

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
        /// @throws result_t
        static void __zecall
        Destroy(
            ModuleBuildLog* pModuleBuildLog                 ///< [in][release] pointer to the module build log object.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves text string for build log.
        /// 
        /// @details
        ///     - The caller can pass nullptr for pBuildLog when querying only for size.
        ///     - The caller must provide memory for build log.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetString(
            size_t* pSize,                                  ///< [in,out] size of build log string.
            char* pBuildLog = nullptr                       ///< [in,out][optional] pointer to null-terminated string of the log.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for kernel
    class Kernel
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_kernel_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported kernel creation flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default driver behavior
            FORCE_RESIDENCY,                                ///< force all device allocations to be resident during execution

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel attributes
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cl_kernel_exec_info**
        enum class attribute_t
        {
            KERNEL_ATTR_INDIRECT_HOST_ACCESS = 0,           ///< Indicates that the function accesses host allocations indirectly
                                                            ///< (default: false, type: bool_t)
            KERNEL_ATTR_INDIRECT_DEVICE_ACCESS,             ///< Indicates that the function accesses device allocations indirectly
                                                            ///< (default: false, type: bool_t)
            KERNEL_ATTR_INDIRECT_SHARED_ACCESS,             ///< Indicates that the function accesses shared allocations indirectly
                                                            ///< (default: false, type: bool_t)
            KERNEL_ATTR_SOURCE_ATTRIBUTE,                   ///< Declared kernel attributes (i.e. can be specified with __attribute__
                                                            ///< in runtime language). (type: char[]) Returned as a null-terminated
                                                            ///< string and each attribute is separated by a space.
                                                            ///< ::zeKernelSetAttribute is not supported for this.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_kernel_properties_t
        enum class properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_KERNEL_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags
            const char* pKernelName = nullptr;              ///< [in] null-terminated name of kernel in module

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel properties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::ZE_KERNEL_PROPERTIES_VERSION_CURRENT
            char name[ZE_MAX_KERNEL_NAME];                  ///< [out] Kernel name
            uint32_t numKernelArgs;                         ///< [out] number of kernel arguments.
            uint32_t requiredGroupSizeX;                    ///< [out] required group size in the X dimension
            uint32_t requiredGroupSizeY;                    ///< [out] required group size in the Y dimension
            uint32_t requiredGroupSizeZ;                    ///< [out] required group size in the Z dimension

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        kernel_handle_t m_handle;                       ///< [in] handle of kernel object
        Module* m_pModule;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the kernel object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Kernel( void ) = delete;
        Kernel( 
            kernel_handle_t handle,                         ///< [in] handle of kernel object
            Module* pModule,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the kernel object
            );

        ~Kernel( void ) = default;

        Kernel( Kernel const& other ) = delete;
        void operator=( Kernel const& other ) = delete;

        Kernel( Kernel&& other ) = delete;
        void operator=( Kernel&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getModule( void ) const { return m_pModule; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Create a kernel object from a module by name
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - Kernel*: handle of the Function object
        /// 
        /// @throws result_t
        static Kernel* __zecall
        Create(
            Module* pModule,                                ///< [in] pointer to the module
            const desc_t* desc                              ///< [in] pointer to kernel descriptor
            );

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
        /// @throws result_t
        static void __zecall
        Destroy(
            Kernel* pKernel                                 ///< [in][release] pointer to the kernel object
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the preferred Intermediate cache configuration for a kernel.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same kernel handle.
        /// @throws result_t
        void __zecall
        SetIntermediateCacheConfig(
            Device::cache_config_t CacheConfig              ///< [in] CacheConfig
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set group size for a kernel
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same kernel handle.
        ///     - The implementation of this function should be lock-free.
        ///     - The implementation will copy the group size information into a command
        ///       list when the function is appended.
        /// @throws result_t
        void __zecall
        SetGroupSize(
            uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
            uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
            uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query a suggested group size for a kernel given a global size for each
        ///        dimension.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        ///     - This function ignores the group size that is set using
        ///       ::zeKernelSetGroupSize.
        /// @returns
        ///     - uint32_t: recommended size of group for X dimension
        ///     - uint32_t: recommended size of group for Y dimension
        ///     - uint32_t: recommended size of group for Z dimension
        /// 
        /// @throws result_t
        std::tuple<uint32_t, uint32_t, uint32_t> __zecall
        SuggestGroupSize(
            uint32_t globalSizeX,                           ///< [in] global width for X dimension
            uint32_t globalSizeY,                           ///< [in] global width for Y dimension
            uint32_t globalSizeZ                            ///< [in] global width for Z dimension
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query a suggested max group count a cooperative kernel.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - uint32_t: recommended total group count.
        /// 
        /// @throws result_t
        uint32_t __zecall
        SuggestMaxCooperativeGroupCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set kernel argument used on kernel launch.
        /// 
        /// @details
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same function handle.
        ///     - The implementation of this function should be lock-free.
        ///     - The implementation will copy the arguments into a command list when
        ///       the function is appended.
        /// @throws result_t
        void __zecall
        SetArgumentValue(
            uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
            size_t argSize,                                 ///< [in] size of argument type
            const void* pArgValue = nullptr                 ///< [in][optional] argument value represented as matching arg type. If
                                                            ///< null then argument value is considered null.
            );

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
        /// @throws result_t
        void __zecall
        SetAttribute(
            attribute_t attr,                               ///< [in] attribute to set
            uint32_t size,                                  ///< [in] size in bytes of kernel attribute value.
            const void* pValue = nullptr                    ///< [in][optional] pointer to attribute value.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Gets a kernel attribute
        /// 
        /// @details
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same function handle.
        ///     - The implementation of this function should be lock-free.
        ///     - The caller sets pValue to nullptr when querying only for size.
        ///     - The caller must provide memory for pValue querying when querying size.
        /// @throws result_t
        void __zecall
        GetAttribute(
            attribute_t attr,                               ///< [in] attribute to get. Documentation for ::ze_kernel_attribute_t for
                                                            ///< return type information for pValue.
            uint32_t* pSize,                                ///< [in,out] size in bytes needed for kernel attribute value. If pValue is
                                                            ///< nullptr then the size needed for pValue memory will be written to
                                                            ///< pSize. Only need to query size for arbitrary sized attributes.
            void* pValue = nullptr                          ///< [in,out][optional] pointer to attribute value result.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve kernel properties.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            properties_t* pKernelProperties                 ///< [in,out] query result for kernel properties.
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_version_t to std::string
    std::string to_string( const Module::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::format_t to std::string
    std::string to_string( const Module::format_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::constants_t to std::string
    std::string to_string( const Module::constants_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_t to std::string
    std::string to_string( const Module::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_version_t to std::string
    std::string to_string( const Kernel::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::flag_t to std::string
    std::string to_string( const Kernel::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_t to std::string
    std::string to_string( const Kernel::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::attribute_t to std::string
    std::string to_string( const Kernel::attribute_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::properties_version_t to std::string
    std::string to_string( const Kernel::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::properties_t to std::string
    std::string to_string( const Kernel::properties_t val );

} // namespace ze
#endif // defined(__cplusplus)
#endif // _ZE_MODULE_HPP
