"""
 Copyright (C) 2019-2025 Intel Corporation

 SPDX-License-Identifier: MIT

 @file zer.py
 @version v1.14-r1.14.33

 """
import platform
from ctypes import *
from enum import *

###############################################################################
__version__ = "1.0"

###############################################################################
## @brief Immediate Command List default descriptor for GPU devices

###############################################################################
## @brief Device Unified Shared Memory Allocation default descriptor for GPU
##        devices

###############################################################################
## @brief Host Unified Shared Memory Allocation default descriptor for GPU
##        devices

###############################################################################
__use_win_types = "Windows" == platform.uname()[0]

###############################################################################
## @brief Function-pointer for zerGetLastErrorDescription
if __use_win_types:
    _zerGetLastErrorDescription_t = WINFUNCTYPE( ze_result_t, POINTER(c_char_p) )
else:
    _zerGetLastErrorDescription_t = CFUNCTYPE( ze_result_t, POINTER(c_char_p) )

###############################################################################
## @brief Function-pointer for zerTranslateDeviceHandleToIdentifier
if __use_win_types:
    _zerTranslateDeviceHandleToIdentifier_t = WINFUNCTYPE( uint32_t, ze_device_handle_t )
else:
    _zerTranslateDeviceHandleToIdentifier_t = CFUNCTYPE( uint32_t, ze_device_handle_t )

###############################################################################
## @brief Function-pointer for zerTranslateIdentifierToDeviceHandle
if __use_win_types:
    _zerTranslateIdentifierToDeviceHandle_t = WINFUNCTYPE( ze_device_handle_t, c_ulong )
else:
    _zerTranslateIdentifierToDeviceHandle_t = CFUNCTYPE( ze_device_handle_t, c_ulong )

###############################################################################
## @brief Function-pointer for zerGetDefaultContext
if __use_win_types:
    _zerGetDefaultContext_t = WINFUNCTYPE( ze_context_handle_t,  )
else:
    _zerGetDefaultContext_t = CFUNCTYPE( ze_context_handle_t,  )


###############################################################################
## @brief Table of Global functions pointers
class _zer_global_dditable_t(Structure):
    _fields_ = [
        ("pfnGetLastErrorDescription", c_void_p),                       ## _zerGetLastErrorDescription_t
        ("pfnTranslateDeviceHandleToIdentifier", c_void_p),             ## _zerTranslateDeviceHandleToIdentifier_t
        ("pfnTranslateIdentifierToDeviceHandle", c_void_p),             ## _zerTranslateIdentifierToDeviceHandle_t
        ("pfnGetDefaultContext", c_void_p)                              ## _zerGetDefaultContext_t
    ]

###############################################################################
class _zer_dditable_t(Structure):
    _fields_ = [
        ("Global", _zer_global_dditable_t)
    ]

###############################################################################
## @brief zer device-driver interfaces
class ZER_DDI:
    def __init__(self, version : ze_api_version_t):
        # load the ze_loader library
        if "Windows" == platform.uname()[0]:
            self.__dll = WinDLL("ze_loader.dll")
        else:
            self.__dll = CDLL("ze_loader.so")

        # fill the ddi tables
        self.__dditable = _zer_dditable_t()

        # call driver to get function pointers
        _Global = _zer_global_dditable_t()
        r = ze_result_v(self.__dll.zerGetGlobalProcAddrTable(version, byref(_Global)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Global = _Global

        # attach function interface to function address
        self.zerGetLastErrorDescription = _zerGetLastErrorDescription_t(self.__dditable.Global.pfnGetLastErrorDescription)
        self.zerTranslateDeviceHandleToIdentifier = _zerTranslateDeviceHandleToIdentifier_t(self.__dditable.Global.pfnTranslateDeviceHandleToIdentifier)
        self.zerTranslateIdentifierToDeviceHandle = _zerTranslateIdentifierToDeviceHandle_t(self.__dditable.Global.pfnTranslateIdentifierToDeviceHandle)
        self.zerGetDefaultContext = _zerGetDefaultContext_t(self.__dditable.Global.pfnGetDefaultContext)

        # success!
