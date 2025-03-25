# Copyright (C) 2020-2024 Intel Corporation
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.12.0 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(THIRD_PARTY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

if(MSVC AND (MSVC_VERSION LESS 1900))
    message(FATAL_ERROR "Visual Studio Compiler Version >= 1900 Required to build.")
endif()

# This project follows semantic versioning (https://semver.org/)
project(level-zero VERSION 1.21.7)

include(GNUInstallDirs)

find_package(Git)
if(Git_FOUND)
	if(MSVC)
		execute_process(
			COMMAND CMD /c ${GIT_EXECUTABLE} rev-parse HEAD
			OUTPUT_VARIABLE VERSION_SHA
			OUTPUT_STRIP_TRAILING_WHITESPACE
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		)
	else()
	execute_process(
		COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
		OUTPUT_VARIABLE VERSION_SHA
		OUTPUT_STRIP_TRAILING_WHITESPACE
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
	endif()
else()
	set(VERSION_SHA " - No git SHA found, compiled outside git folder.")
endif()
add_definitions(-DLOADER_VERSION_SHA="${VERSION_SHA}")

if(SYSTEM_SPDLOG)
	find_package(spdlog CONFIG)
	if(spdlog_FOUND)
		message(STATUS "System spdlog found.")
	else()
		message(FATAL_ERROR "SYSTEM_SPDLOG specified but spdlog wasn't found.")
	endif()
else()
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/spdlog_headers")
endif()

include(FetchContent)

if(BUILD_L0_LOADER_TESTS AND (NOT MSVC OR (MSVC AND NOT BUILD_STATIC)))
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )
    add_library(GTest::GTest INTERFACE IMPORTED)
    target_link_libraries(GTest::GTest INTERFACE gtest_main)

	# For Windows: Prevent overriding the parent project's compiler/linker settings
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

	FetchContent_MakeAvailable(googletest)

	enable_testing()
endif()

# Update other relevant variables to include the patch
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(CMAKE_PROJECT_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CMAKE_PROJECT_VERSION "${PROJECT_VERSION}")
add_definitions(-DLOADER_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DLOADER_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DLOADER_VERSION_PATCH=${PROJECT_VERSION_PATCH})

file(WRITE "${CMAKE_BINARY_DIR}/VERSION" "${PROJECT_VERSION}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#Define a path for custom commands to work around MSVC
set(CUSTOM_COMMAND_BINARY_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
if(MSVC)
    #MSVC implicitly adds $<CONFIG> to the output path
    set(CUSTOM_COMMAND_BINARY_DIR ${CUSTOM_COMMAND_BINARY_DIR}/$<CONFIG>)
    #enabling Control Flow Guard
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /guard:cf")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /guard:cf")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DYNAMICBASE")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /DYNAMICBASE")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_CXX_LINKER_WRAPPER_FLAG}/DYNAMICBASE")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_CXX_LINKER_WRAPPER_FLAG}/guard:cf")
    # enable Spectre Mitigation, not supported by clang-cl
    if((NOT CMAKE_CXX_COMPILER_ID STREQUAL Clang) AND (NOT CMAKE_CXX_COMPILER_ID STREQUAL IntelLLVM))
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qspectre")
    endif()
    if((NOT CMAKE_C_COMPILER_ID STREQUAL Clang) AND NOT (CMAKE_C_COMPILER_ID STREQUAL IntelLLVM))
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Qspectre")
    endif()
endif()

#CXX compiler support
if(NOT MSVC)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
    if(COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support.  Please use a different C++ compiler.")
    endif()
    if (UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -fPIC")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
    endif()
    if(NOT CMAKE_CXX_COMPILER_ID STREQUAL IntelLLVM)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wnon-virtual-dtor")
    endif()
endif()

#MSVC compile flags
if(MSVC)
    IF (NOT MSVC_BUILD_L0_DYNAMIC_VCRUNTIME)
        string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    ELSE()
        string(REPLACE "/MTd" "/MDd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        string(REPLACE "/MT" "/MD" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
        if(NOT (CMAKE_CXX_FLAGS_RELEASE MATCHES "/MD"))
            set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
        endif()
        if(NOT (CMAKE_CXX_FLAGS_DEBUG MATCHES "/MDd"))
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
        endif()
    ENDIF()

    if(NOT CMAKE_CXX_COMPILER_ID STREQUAL IntelLLVM)
        # treat warnings as errors
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /W3")
    endif()

    # enable multi-process compilation, not supported by clang-cl
    if((NOT CMAKE_CXX_COMPILER_ID STREQUAL Clang) AND (NOT CMAKE_CXX_COMPILER_ID STREQUAL IntelLLVM))
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    endif()

    # enable exceptions handling
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

    # enable creation of PDB files for Release Builds
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} ${CMAKE_CXX_LINKER_WRAPPER_FLAG}/DEBUG ${CMAKE_CXX_LINKER_WRAPPER_FLAG}/OPT:REF ${CMAKE_CXX_LINKER_WRAPPER_FLAG}/OPT:ICF")

    # enable CET shadow stack
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_CXX_LINKER_WRAPPER_FLAG}/CETCOMPAT")

    #Use of sccache with MSVC requires workaround of replacing /Zi with /Z7
    #https://github.com/mozilla/sccache
    if(USE_Z7) #sccache
      string(REPLACE "/Zi" "/Z7" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
      string(REPLACE "/Zi" "/Z7" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
      string(REPLACE "/Zi" "/Z7" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
      string(REPLACE "/Zi" "/Z7" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
      string(REPLACE "/Zi" "/Z7" CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
      string(REPLACE "/Zi" "/Z7" CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO}")
    endif()

endif()

if(USE_ASAN)
    if(NOT MSVC)
        # -fno-omit-frame-pointer is included for nicer stack traces in error messages
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=address")
    else()
        message(WARNING "Address Sanitizer is not supported on Windows")
    endif()
endif()

# Enable -Werror only if not building as a subproject. For subprojects, leave
# this up to the parent project.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  if(CMAKE_VERSION VERSION_LESS 3.24)
    if(NOT MSVC)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
    endif()
  else()
    set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
  endif()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/wrapper/include)


include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(TARGET_LOADER_NAME ze_loader)


add_subdirectory(source)
add_subdirectory(samples)

if(BUILD_L0_LOADER_TESTS AND (NOT MSVC OR (MSVC AND NOT BUILD_STATIC)))
    include(CTest)
    add_subdirectory(test)
endif()

include("os_release_info.cmake")
get_os_release_info(os_name os_version os_codename)
string(APPEND os_type "${os_name}")
string(COMPARE EQUAL "${os_type}" "sles" sles_distro)
#Pick only first character of os_name
string(SUBSTRING "${os_name}" 0 1 os_name)

file(GLOB LEVEL_ZERO_API_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

set(SDK_COMPONENT_STRING "level-zero-devel")

if(BUILD_INSTALLER)
    set(SDK_COMPONENT_STRING "SDK")
endif()

install(FILES ${LEVEL_ZERO_API_HEADERS}
    DESTINATION ./include/level_zero
    COMPONENT ${SDK_COMPONENT_STRING}
)

file(GLOB LEVEL_ZERO_LAYERS_API_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/layers/*.h")

install(FILES ${LEVEL_ZERO_LAYERS_API_HEADERS}
    DESTINATION ./include/level_zero/layers
    COMPONENT ${SDK_COMPONENT_STRING}
)

file(GLOB LEVEL_ZERO_LOADER_API_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/loader/*.h")

install(FILES ${LEVEL_ZERO_LOADER_API_HEADERS}
    DESTINATION ./include/level_zero/loader
    COMPONENT ${SDK_COMPONENT_STRING}
)

# If generators list was not define build native package for current distro
if(NOT DEFINED CPACK_GENERATOR)
	if(EXISTS "/etc/debian_version")
		set(CPACK_GENERATOR "DEB")
	elseif(EXISTS "/etc/redhat-release")
		set(CPACK_GENERATOR "RPM")
	elseif(EXISTS "/etc/SUSE-brand" OR EXISTS "/etc/SUSE-release" OR sles_distro)
		set(CPACK_GENERATOR "RPM")
    elseif(BUILD_INSTALLER)
        set(PRODUCT_GUID_FILE "${CMAKE_SOURCE_DIR}/PRODUCT_GUID.txt")
        if(EXISTS "${PRODUCT_GUID_FILE}")
            file(STRINGS "${PRODUCT_GUID_FILE}" SAVED_PRODUCT_GUID)
            list(GET SAVED_PRODUCT_GUID 0 SAVED_PRODUCT_GUID_VERSION)
            message(STATUS "Saved Product GUID: ${SAVED_PRODUCT_GUID_VERSION}")
            message(STATUS "project version: ${PROJECT_VERSION}")
            if(NOT SAVED_PRODUCT_GUID_VERSION STREQUAL "${PROJECT_VERSION}")

            execute_process(
                COMMAND python ${CMAKE_SOURCE_DIR}/scripts/generate_wix_guid.py
                OUTPUT_VARIABLE GENERATED_PRODUCT_GUID
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )
            file(WRITE "${PRODUCT_GUID_FILE}" "${PROJECT_VERSION}\n${GENERATED_PRODUCT_GUID}")
            message(STATUS "Generated Product GUID: ${GENERATED_PRODUCT_GUID} for version ${PROJECT_VERSION}")
            else()
            string(REPLACE "\n" ";" GUID_CONTENTS "${SAVED_PRODUCT_GUID}")
            list(GET GUID_CONTENTS 1 GENERATED_PRODUCT_GUID)
            endif()
        else()
            execute_process(
            COMMAND python ${CMAKE_SOURCE_DIR}/scripts/generate_wix_guid.py
            OUTPUT_VARIABLE GENERATED_PRODUCT_GUID
            OUTPUT_STRIP_TRAILING_WHITESPACE
            )
            file(WRITE "${PRODUCT_GUID_FILE}" "${PROJECT_VERSION}\n${GENERATED_PRODUCT_GUID}")
        endif()
        message(STATUS "Using Product GUID: ${GENERATED_PRODUCT_GUID} for version ${PROJECT_VERSION}")
        set(CPACK_GENERATOR "WIX")
        set(CPACK_PACKAGE_NAME "oneAPI Level Zero")
        set(CPACK_PACKAGE_FILE_NAME "oneAPI_Level_Zero-${PROJECT_VERSION}-win64")
        set(CPACK_WIX_ROOT_FEATURE_TITLE "oneAPI Level Zero")
        set(CPACK_WIX_PROGRAM_MENU_FOLDER "oneAPI Level Zero")

        set(CMAKE_INSTALL_PREFIX "LevelZeroSDK/${PROJECT_VERSION}/")
        # Add the script to the install directory
        install(FILES "${CMAKE_SOURCE_DIR}/scripts/level_zero_sdk_setup.ps1"
            DESTINATION ./scripts
            COMPONENT ${SDK_COMPONENT_STRING}
        )

        set(CPACK_WIX_PATCH_FILE "${CMAKE_SOURCE_DIR}/scripts/wix_env_installation.wxs")

        # sharing GUIDs between product and upgrade codes such that side by side installation is allowed.
        set(CPACK_WIX_PRODUCT_GUID ${GENERATED_PRODUCT_GUID})
        set(CPACK_WIX_UPGRADE_GUID ${GENERATED_PRODUCT_GUID})
        set(CPACK_WIX_UI_DIALOG "${CMAKE_SOURCE_DIR}/icons/oneapi-icon-left-aligned.png")
        set(CPACK_WIX_UI_BANNER "${CMAKE_SOURCE_DIR}/icons/oneapi-icon-right-aligned.png")
        get_cmake_property(CPACK_COMPONENTS_ALL COMPONENTS)
        list(REMOVE_ITEM CPACK_COMPONENTS_ALL "Loader")
        set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSES/MIT.txt")
	else()
		set(CPACK_GENERATOR "ZIP")
	endif()
endif()

if(MSVC)
	set(CPACK_SET_DESTDIR FALSE)
	set(CPACK_PACKAGING_INSTALL_PREFIX "")
else()
	set(CPACK_SET_DESTDIR TRUE)
endif()
set(CPACK_PACKAGE_RELOCATABLE FALSE)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "oneAPI Level Zero")
set(CPACK_PACKAGE_VENDOR "Intel")

set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_CONTACT "Intel Corporation")

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

if(CPACK_GENERATOR MATCHES "RPM")
	set(CPACK_RPM_COMPRESSION_TYPE "xz")
	string(FIND "${CMAKE_CXX_COMPILER}" "aarch64" compiler_arch_check)
	if((NOT ${compiler_arch_check} MATCHES "-1") OR (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch64"))
		set(CPACK_RPM_PACKAGE_ARCHITECTURE "aarch64")
	elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
		set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
	endif()
	set(CPACK_RPM_PACKAGE_AUTOREQ OFF)
	set(CPACK_RPM_PACKAGE_DESCRIPTION "oneAPI Level Zero")
	set(CPACK_RPM_PACKAGE_GROUP "System Environment/Libraries")
	set(CPACK_RPM_PACKAGE_LICENSE "MIT")
	set(CPACK_RPM_PACKAGE_RELEASE 1)
	set(CPACK_RPM_PACKAGE_RELEASE_DIST ON)
	set(CPACK_RPM_PACKAGE_URL "https://github.com/oneapi-src/level-zero")
	set(CPACK_RPM_COMPONENT_INSTALL ON)
	set(CPACK_RPM_LEVEL-ZERO_PACKAGE_NAME "${PROJECT_NAME}")
	set(CPACK_RPM_LEVEL-ZERO-DEVEL_PACKAGE_NAME "${PROJECT_NAME}-devel")
	set(CPACK_RPM_LEVEL-ZERO_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-${os_name}${os_version}.${CPACK_RPM_PACKAGE_ARCHITECTURE}.rpm")
	set(CPACK_RPM_LEVEL-ZERO-DEVEL_FILE_NAME "${PROJECT_NAME}-devel-${PROJECT_VERSION}-${os_name}${os_version}.${CPACK_RPM_PACKAGE_ARCHITECTURE}.rpm")
	set(CPACK_RPM_LEVEL-ZERO-DEVEL_PACKAGE_REQUIRES "level-zero = ${PROJECT_VERSION}")


	set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION
	  /etc/ld.so.conf.d
	  /usr/local
	  /usr/local/lib64
	  /usr/local/bin
	  /usr/local/include
	)
endif()

if(CPACK_GENERATOR MATCHES "DEB")
	string(FIND "${CMAKE_CXX_COMPILER}" "aarch64" compiler_arch_check)
	if((NOT ${compiler_arch_check} MATCHES "-1") OR (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch64"))
		SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE arm64)
	elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
		SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
	endif()
	set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/oneapi-src/level-zero")
	set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
	set(CPACK_DEBIAN_LEVEL-ZERO_PACKAGE_NAME "${PROJECT_NAME}")
	set(CPACK_DEBIAN_LEVEL-ZERO-DEVEL_PACKAGE_NAME "${PROJECT_NAME}-devel")
    set(CPACK_DEBIAN_LEVEL-ZERO_FILE_NAME "${PROJECT_NAME}_${PROJECT_VERSION}+${os_name}${os_version}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}.deb")
    set(CPACK_DEBIAN_LEVEL-ZERO-DEVEL_FILE_NAME "${PROJECT_NAME}-devel_${PROJECT_VERSION}+${os_name}${os_version}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}.deb")
    set(CPACK_DEBIAN_LEVEL-ZERO-DEVEL_PACKAGE_DEPENDS "level-zero(=${PROJECT_VERSION})")
    set(CPACK_DEB_COMPONENT_INSTALL ON)
    set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
endif()

INCLUDE(CPack)
