/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_image.h
 *
 * @brief Intel 'One API' Level-Zero APIs for Images
 *
 */
 
#ifndef _ZE_IMAGE_H
#define _ZE_IMAGE_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZE_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_image_desc_t
typedef enum _ze_image_desc_version_t
{
    ZE_IMAGE_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),   ///< version 0.91

} ze_image_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image creation flags
typedef enum _ze_image_flag_t
{
    ZE_IMAGE_FLAG_PROGRAM_READ = ZE_BIT( 0 ),       ///< programs will read contents
    ZE_IMAGE_FLAG_PROGRAM_WRITE = ZE_BIT( 1 ),      ///< programs will write contents
    ZE_IMAGE_FLAG_BIAS_CACHED = ZE_BIT( 2 ),        ///< device should cache contents
    ZE_IMAGE_FLAG_BIAS_UNCACHED = ZE_BIT( 3 ),      ///< device should not cache contents

} ze_image_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image types
typedef enum _ze_image_type_t
{
    ZE_IMAGE_TYPE_1D,                               ///< 1D
    ZE_IMAGE_TYPE_1DARRAY,                          ///< 1D array
    ZE_IMAGE_TYPE_2D,                               ///< 2D
    ZE_IMAGE_TYPE_2DARRAY,                          ///< 2D array
    ZE_IMAGE_TYPE_3D,                               ///< 3D
    ZE_IMAGE_TYPE_BUFFER,                           ///< Buffer

} ze_image_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image format layouts
typedef enum _ze_image_format_layout_t
{
    ZE_IMAGE_FORMAT_LAYOUT_8,                       ///< 8-bit single component layout
    ZE_IMAGE_FORMAT_LAYOUT_16,                      ///< 16-bit single component layout
    ZE_IMAGE_FORMAT_LAYOUT_32,                      ///< 32-bit single component layout
    ZE_IMAGE_FORMAT_LAYOUT_8_8,                     ///< 2-component 8-bit layout
    ZE_IMAGE_FORMAT_LAYOUT_8_8_8_8,                 ///< 4-component 8-bit layout
    ZE_IMAGE_FORMAT_LAYOUT_16_16,                   ///< 2-component 16-bit layout
    ZE_IMAGE_FORMAT_LAYOUT_16_16_16_16,             ///< 4-component 16-bit layout
    ZE_IMAGE_FORMAT_LAYOUT_32_32,                   ///< 2-component 32-bit layout
    ZE_IMAGE_FORMAT_LAYOUT_32_32_32_32,             ///< 4-component 32-bit layout
    ZE_IMAGE_FORMAT_LAYOUT_10_10_10_2,              ///< 4-component 10_10_10_2 layout
    ZE_IMAGE_FORMAT_LAYOUT_11_11_10,                ///< 3-component 11_11_10 layout
    ZE_IMAGE_FORMAT_LAYOUT_5_6_5,                   ///< 3-component 5_6_5 layout
    ZE_IMAGE_FORMAT_LAYOUT_5_5_5_1,                 ///< 4-component 5_5_5_1 layout
    ZE_IMAGE_FORMAT_LAYOUT_4_4_4_4,                 ///< 4-component 4_4_4_4 layout
    ZE_IMAGE_FORMAT_LAYOUT_Y8,                      ///< Media Format: Y8. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_NV12,                    ///< Media Format: NV12. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_YUYV,                    ///< Media Format: YUYV. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_VYUY,                    ///< Media Format: VYUY. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_YVYU,                    ///< Media Format: YVYU. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_UYVY,                    ///< Media Format: UYVY. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_AYUV,                    ///< Media Format: AYUV. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_YUAV,                    ///< Media Format: YUAV. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_P010,                    ///< Media Format: P010. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_Y410,                    ///< Media Format: Y410. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_P012,                    ///< Media Format: P012. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_Y16,                     ///< Media Format: Y16. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_P016,                    ///< Media Format: P016. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_Y216,                    ///< Media Format: Y216. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_P216,                    ///< Media Format: P216. Format type and swizzle is ignored for this.
    ZE_IMAGE_FORMAT_LAYOUT_P416,                    ///< Media Format: P416. Format type and swizzle is ignored for this.

} ze_image_format_layout_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image format types
typedef enum _ze_image_format_type_t
{
    ZE_IMAGE_FORMAT_TYPE_UINT,                      ///< Unsigned integer
    ZE_IMAGE_FORMAT_TYPE_SINT,                      ///< Signed integer
    ZE_IMAGE_FORMAT_TYPE_UNORM,                     ///< Unsigned normalized integer
    ZE_IMAGE_FORMAT_TYPE_SNORM,                     ///< Signed normalized integer
    ZE_IMAGE_FORMAT_TYPE_FLOAT,                     ///< Float

} ze_image_format_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image format component swizzle into channel
typedef enum _ze_image_format_swizzle_t
{
    ZE_IMAGE_FORMAT_SWIZZLE_R,                      ///< Red component
    ZE_IMAGE_FORMAT_SWIZZLE_G,                      ///< Green component
    ZE_IMAGE_FORMAT_SWIZZLE_B,                      ///< Blue component
    ZE_IMAGE_FORMAT_SWIZZLE_A,                      ///< Alpha component
    ZE_IMAGE_FORMAT_SWIZZLE_0,                      ///< Zero
    ZE_IMAGE_FORMAT_SWIZZLE_1,                      ///< One
    ZE_IMAGE_FORMAT_SWIZZLE_X,                      ///< Don't care

} ze_image_format_swizzle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Image format descriptor
typedef struct _ze_image_format_desc_t
{
    ze_image_format_layout_t layout;                ///< [in] image format component layout
    ze_image_format_type_t type;                    ///< [in] image format type. Media formats can't be used for
                                                    ///< ::ZE_IMAGE_TYPE_BUFFER.
    ze_image_format_swizzle_t x;                    ///< [in] image component swizzle into channel x
    ze_image_format_swizzle_t y;                    ///< [in] image component swizzle into channel y
    ze_image_format_swizzle_t z;                    ///< [in] image component swizzle into channel z
    ze_image_format_swizzle_t w;                    ///< [in] image component swizzle into channel w

} ze_image_format_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Image descriptor
typedef struct _ze_image_desc_t
{
    ze_image_desc_version_t version;                ///< [in] ::ZE_IMAGE_DESC_VERSION_CURRENT
    ze_image_flag_t flags;                          ///< [in] creation flags
    ze_image_type_t type;                           ///< [in] image type
    ze_image_format_desc_t format;                  ///< [in] image format
    uint64_t width;                                 ///< [in] width in pixels for ::ze_image_type_t::1D/2D/3D and bytes for
                                                    ///< Buffer, see ::ze_device_image_properties_t::maxImageDims1D/2D/3D and
                                                    ///< maxImageBufferSize.
    uint32_t height;                                ///< [in] height in pixels (2D or 3D only), see
                                                    ///< ::ze_device_image_properties_t::maxImageDims2D/3D
    uint32_t depth;                                 ///< [in] depth in pixels (3D only), see
                                                    ///< ::ze_device_image_properties_t::maxImageDims3D
    uint32_t arraylevels;                           ///< [in] array levels (array types only), see
                                                    ///< ::ze_device_image_properties_t::maxImageArraySlices
    uint32_t miplevels;                             ///< [in] mipmap levels (must be 0)

} ze_image_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_image_properties_t
typedef enum _ze_image_properties_version_t
{
    ZE_IMAGE_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ), ///< version 0.91

} ze_image_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported sampler filtering flags
typedef enum _ze_image_sampler_filter_flags_t
{
    ZE_IMAGE_SAMPLER_FILTER_FLAGS_NONE = 0,         ///< device does not support filtering
    ZE_IMAGE_SAMPLER_FILTER_FLAGS_POINT = ZE_BIT(0),///< device supports point filtering
    ZE_IMAGE_SAMPLER_FILTER_FLAGS_LINEAR = ZE_BIT(1),   ///< device supports linear filtering

} ze_image_sampler_filter_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Image properties
typedef struct _ze_image_properties_t
{
    ze_image_properties_version_t version;          ///< [in] ::ZE_IMAGE_PROPERTIES_VERSION_CURRENT
    ze_image_sampler_filter_flags_t samplerFilterFlags; ///< [out] supported sampler filtering

} ze_image_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves supported properties of an image.
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
///         + `nullptr == desc`
///         + `nullptr == pImageProperties`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_IMAGE_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
///         + desc->type
__ze_api_export ze_result_t __zecall
zeImageGetProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    ze_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a image object on the device.
/// 
/// @details
///     - The image is only visible to the device on which it was created.
///     - The image can be copied to another device using the
///       ::::zeCommandListAppendImageCopy functions.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clCreateImage
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phImage`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_IMAGE_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
///         + desc->type
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeImageCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a image object.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the image before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this image
///     - The application may **not** call this function from simultaneous
///       threads with the same image handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hImage`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeImageDestroy(
    ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_IMAGE_H
