<%!
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/*
 * ***THIS FILE IS GENERATED. ***
 * See to_string.h.mako for modifications
 *
 * Copyright (C) 2025-2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}
 * 
 * to_string functions for Level Zero types
 */

#ifndef _${N}_TO_STRING_H
#define _${N}_TO_STRING_H

#include "${x}_api.h"
#include <string>
#include <sstream>
#include <iomanip>

%if n == 'ze':
namespace loader {

// Forward declarations
std::string to_string(const ${x}_result_t result);

// Pointer to_string
template<typename T>
inline std::string to_string(const T* ptr) {
    if (ptr == nullptr) {
        return "nullptr";
    }
    std::ostringstream oss;
    oss << "0x" << std::hex << reinterpret_cast<uintptr_t>(ptr);
    return oss.str();
}

%else:
// Include ze_to_string.h for common definitions
#include "ze_to_string.h"

namespace loader {
%endif
%if n == 'ze':
// Handle to_string functions
%for obj in th.extract_objs(specs, r"handle"):
inline std::string to_string(${th.make_type_name(n, tags, obj)} handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

%endfor
%endif
%if n == 'ze':
// For primitive types and Level Zero typedef'd types
// Since most Level Zero types are typedef'd to uint32_t, we can't distinguish them by type
inline std::string to_string(uint32_t value) { return std::to_string(value); }
inline std::string to_string(uint64_t value) { return std::to_string(value); }
inline std::string to_string(uint8_t value) { return std::to_string(static_cast<unsigned>(value)); }
inline std::string to_string(uint16_t value) { return std::to_string(value); }
inline std::string to_string(int32_t value) { return std::to_string(value); }
inline std::string to_string(int64_t value) { return std::to_string(value); }
#if SIZE_MAX != UINT64_MAX
inline std::string to_string(size_t value) { return std::to_string(value); }
#endif
inline std::string to_string(double value) { return std::to_string(value); }
inline std::string to_string(const char* str) {
    if (!str) return "nullptr";
    return std::string("\"") + str + "\"";
}

// Pointer to primitive types - dereference and print value
inline std::string to_string(const uint32_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
inline std::string to_string(const uint64_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
inline std::string to_string(const uint8_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
inline std::string to_string(const uint16_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
inline std::string to_string(const int32_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
inline std::string to_string(const int64_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
#if SIZE_MAX != UINT64_MAX
inline std::string to_string(const size_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
#endif
inline std::string to_string(const double* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}

%endif
// Struct to_string functions
%for obj in th.extract_objs(specs, r"struct"):
<%
    struct_name = th.make_type_name(n, tags, obj)
%>\
inline std::string to_string(const ${struct_name}* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    %for idx, member in enumerate(obj['members']):
    %if member['name'] != 'pNext':
<%
        # Extract the actual member name without array brackets
        member_name_full = member['name']
        member_name = member_name_full.split('[')[0] if '[' in member_name_full else member_name_full
        is_array = '[' in member_name_full
        
        # Check if member is a pointer or regular value
        member_type = member.get('type', '')
        if is_array:
            # For arrays, just pass the array name (decays to pointer)
            member_access = f"desc->{member_name}"
        elif '*' in member_type:
            # It's already a pointer - pass directly
            member_access = f"desc->{member_name}"
        else:
            # Check if it's a struct type by looking at the type name
            # If it contains a struct typename pattern, take its address
            if '_t' in member_type and 'uint' not in member_type and 'int' not in member_type and 'size_t' not in member_type:
                member_access = f"&desc->{member_name}"
            else:
                member_access = f"desc->{member_name}"
%>\
    %if idx == 0 and member['name'] == 'stype':
    oss << "stype=" << to_string(${member_access});
    %elif idx == 0:
    oss << "${member_name}=" << to_string(${member_access});
    %else:
    oss << ", ${member_name}=" << to_string(${member_access});
    %endif
    %endif
    %endfor
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ${struct_name}& desc) {
    return to_string(&desc);
}

%endfor
} // namespace loader

#endif // _${N}_TO_STRING_H
