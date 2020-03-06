/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_module.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Module
 *
 */
#ifndef _ZET_MODULE_HPP
#define _ZET_MODULE_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for module
    class Module : public ze::Module
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported module debug info formats.
        enum class debug_info_format_t
        {
            ELF_DWARF,                                      ///< Format is ELF/DWARF

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Module::Module;

        ~Module( void ) = default;

        Module( Module const& other ) = delete;
        void operator=( Module const& other ) = delete;

        Module( Module&& other ) = delete;
        void operator=( Module&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve debug info from module.
        /// 
        /// @details
        ///     - The caller can pass nullptr for pDebugInfo when querying only for
        ///       size.
        ///     - The implementation will copy the native binary into a buffer supplied
        ///       by the caller.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetDebugInfo(
            debug_info_format_t format,                     ///< [in] debug info format requested
            size_t* pSize,                                  ///< [in,out] size of debug info in bytes
            uint8_t* pDebugInfo = nullptr                   ///< [in,out][optional] byte pointer to debug info
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for kernel
    class Kernel : public ze::Kernel
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zet_profile_info_t
        enum class profile_info_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supportted profile features
        enum class profile_flag_t
        {
            REGISTER_REALLOCATION = ZE_BIT(0),              ///< request the compiler attempt to minimize register usage as much as
                                                            ///< possible to allow for instrumentation
            FREE_REGISTER_INFO = ZE_BIT(1),                 ///< request the compiler generate free register info

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported profile token types
        enum class profile_token_type_t
        {
            FREE_REGISTER,                                  ///< GRF info

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Profiling meta-data for instrumentation
        struct profile_info_t
        {
            profile_info_version_t version = profile_info_version_t::CURRENT;   ///< [in] ::ZET_PROFILE_INFO_VERSION_CURRENT
            profile_flag_t flags;                           ///< [out] indicates which flags were enabled during compilation
            uint32_t numTokens;                             ///< [out] number of tokens immediately following this structure

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Profile free register token detailing unused registers in the current
        ///        function
        struct profile_free_register_token_t
        {
            profile_token_type_t type;                      ///< [out] type of token
            uint32_t size;                                  ///< [out] total size of the token, in bytes
            uint32_t count;                                 ///< [out] number of register sequences immediately following this
                                                            ///< structure

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Profile register sequence detailing consecutive bytes, all of which
        ///        are unused
        struct profile_register_sequence_t
        {
            uint32_t start;                                 ///< [out] starting byte in the register table, representing the start of
                                                            ///< unused bytes in the current function
            uint32_t count;                                 ///< [out] number of consecutive bytes in the sequence, starting from start

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Kernel::Kernel;

        ~Kernel( void ) = default;

        Kernel( Kernel const& other ) = delete;
        void operator=( Kernel const& other ) = delete;

        Kernel( Kernel&& other ) = delete;
        void operator=( Kernel&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve profiling information generated for the kernel.
        /// 
        /// @details
        ///     - Module must be created using the following build option:
        ///         + "-zet-profile-flags <n>" - enable generation of profile
        ///           information
        ///         + "<n>" must be a combination of ::zet_profile_flag_t, in hex
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - profile_info_t: pointer to profile info
        /// 
        /// @throws result_t
        profile_info_t __zecall
        GetProfileInfo(
            void
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::debug_info_format_t to std::string
    std::string to_string( const Module::debug_info_format_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_info_version_t to std::string
    std::string to_string( const Kernel::profile_info_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_flag_t to std::string
    std::string to_string( const Kernel::profile_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_info_t to std::string
    std::string to_string( const Kernel::profile_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_token_type_t to std::string
    std::string to_string( const Kernel::profile_token_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_free_register_token_t to std::string
    std::string to_string( const Kernel::profile_free_register_token_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_register_sequence_t to std::string
    std::string to_string( const Kernel::profile_register_sequence_t val );

} // namespace zet
#endif // defined(__cplusplus)
#endif // _ZET_MODULE_HPP
