# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)

# This project follows semantic versioning (https://semver.org/). Only set the
# major and minor version here - patch version is determined dynamically.
project(level-zero VERSION 0.91)

# Patch version corresponds to # of commits on master since last version
# major/minor tag (e.g., v1.0). If not building in a git repository, then get
# the patch version from a VERSION_PATCH file that would be shipped with a
# source distribution.
if(EXISTS "${CMAKE_SOURCE_DIR}/VERSION_PATCH")
	file(READ "${CMAKE_SOURCE_DIR}/VERSION_PATCH" VERSION_PATCH)
	string(STRIP "${VERSION_PATCH}" PROJECT_VERSION_PATCH)
	message(STATUS "Using patch version from VERSION_PATCH file in source tree: ${PROJECT_VERSION_PATCH}")
else()
	find_program(GIT_EXE NAMES "git" REQUIRED)
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/.git")
		message(ERROR "Cannot determine patch version - VERSION_PATCH file is not in source tree and source tree does not appear to be a git repository")
	endif()
	set(GIT_TAG "v${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
	if(MSVC)
		execute_process(
			COMMAND CMD /c git -C "${CMAKE_SOURCE_DIR}" rev-list ${GIT_TAG}..HEAD --count
			OUTPUT_VARIABLE VERSION_PATCH
		)
	else()
		execute_process(
			COMMAND git -C "${CMAKE_SOURCE_DIR}" rev-list ${GIT_TAG}..HEAD --count
			OUTPUT_VARIABLE VERSION_PATCH
		)
	endif()
	string(STRIP "${VERSION_PATCH}" PROJECT_VERSION_PATCH)
	if(PROJECT_VERSION_PATCH STREQUAL "")
		message(ERROR "Cannot determine patch version - couldn't find ${GIT_TAG} tag in repository")
	endif()
	message(STATUS "Using patch version from commit count in git repository: ${PROJECT_VERSION_PATCH}")
endif()

# Update other relevant variables to include the patch
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(CMAKE_PROJECT_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CMAKE_PROJECT_VERSION "${PROJECT_VERSION}")

file(WRITE "${CMAKE_BINARY_DIR}/VERSION" "${PROJECT_VERSION}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#Define a path for custom commands to work around MSVC
set(CUSTOM_COMMAND_BINARY_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
if(MSVC)
    #MSVC implicitly adds $<CONFIG> to the output path
    set(CUSTOM_COMMAND_BINARY_DIR ${CUSTOM_COMMAND_BINARY_DIR}/$<CONFIG>)
endif()

# Use same CL version defined in the runtimes
add_definitions(-DCL_TARGET_OPENCL_VERSION=220)
find_path(OpenCL_INCLUDE_DIR
  NAMES CL
  PATHS
    ${OPENCL_PATH}
    "/usr/include/"
  NO_DEFAULT_PATH
)
if(OpenCL_INCLUDE_DIR STREQUAL "OpenCL_INCLUDE_DIR-NOTFOUND")
  message(FATAL_ERROR "OpenCL headers required for interop APIs")
endif()
include_directories(${OpenCL_INCLUDE_DIR})

#CXX compiler support
if(NOT MSVC)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support.  Please use a different C++ compiler.")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -fPIC")
endif()

#MSVC compile flags
if(MSVC)
    string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

    # treat warnings as errors
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /W3 /wd4996")

    # enable multi-process compilation
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

# Option to disable tests
option(${PROJECT_NAME}_BUILD_TESTS "Build unit tests." ON)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/tools)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/wrapper/core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/wrapper/tools)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(source)

include("os_release_info.cmake")
get_os_release_info(os_name os_version os_codename)
#Pick only first character of os_name
string(SUBSTRING "${os_name}" 0 1 os_name)

file(GLOB_RECURSE LEVEL_ZERO_API_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

install(FILES ${LEVEL_ZERO_API_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/level_zero/
    COMPONENT level-zero-devel
)

# If generators list was not define build native package for current distro
if(NOT DEFINED CPACK_GENERATOR)
	if(EXISTS "/etc/debian_version")
		set(CPACK_GENERATOR "DEB")
	elseif(EXISTS "/etc/redhat-release")
		set(CPACK_GENERATOR "RPM")
	else()
		set(CPACK_GENERATOR "TXZ")
	endif()
endif()

set(CPACK_SET_DESTDIR TRUE)
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
	set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
	set(CPACK_RPM_PACKAGE_AUTOREQ OFF)
	set(CPACK_RPM_PACKAGE_DESCRIPTION "oneAPI Level Zero")
	set(CPACK_RPM_PACKAGE_GROUP "System Environment/Libraries")
	set(CPACK_RPM_PACKAGE_LICENSE "MIT")
	set(CPACK_RPM_PACKAGE_RELEASE 1)
	set(CPACK_RPM_PACKAGE_RELEASE_DIST ON)
	set(CPACK_RPM_PACKAGE_URL "http://01.org/compute-runtime")
	set(CPACK_RPM_COMPONENT_INSTALL ON)
	set(CPACK_RPM_LEVEL-ZERO_PACKAGE_NAME "${PROJECT_NAME}")
	set(CPACK_RPM_LEVEL-ZERO-DEVEL_PACKAGE_NAME "${PROJECT_NAME}-devel")
	set(CPACK_RPM_LEVEL-ZERO_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-${os_name}${os_version}.${CPACK_RPM_PACKAGE_ARCHITECTURE}.rpm")
	set(CPACK_RPM_LEVEL-ZERO-DEVEL_FILE_NAME "${PROJECT_NAME}-devel-${PROJECT_VERSION}-${os_name}${os_version}.${CPACK_RPM_PACKAGE_ARCHITECTURE}.rpm")
	set(CPACK_RPM_LEVEL-ZERO-DEVEL_PACKAGE_REQUIRES "opencl-headers >= 2.2-0, level-zero = ${PROJECT_VERSION}")


	set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION
	  /etc/ld.so.conf.d
	  /usr/local
	  /usr/local/lib64
	  /usr/local/bin
	  /usr/local/include
	)
endif()

if(CPACK_GENERATOR MATCHES "DEB")
	set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
	#set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://01.org/compute-runtime")
	set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
	set(CPACK_DEBIAN_LEVEL-ZERO_PACKAGE_NAME "${PROJECT_NAME}")
	set(CPACK_DEBIAN_LEVEL-ZERO-DEVEL_PACKAGE_NAME "${PROJECT_NAME}-devel")
    set(CPACK_DEBIAN_LEVEL-ZERO_FILE_NAME "${PROJECT_NAME}_${PROJECT_VERSION}+${os_name}${os_version}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}.deb")
    set(CPACK_DEBIAN_LEVEL-ZERO-DEVEL_FILE_NAME "${PROJECT_NAME}-devel_${PROJECT_VERSION}+${os_name}${os_version}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}.deb")
    set(CPACK_DEBIAN_LEVEL-ZERO-DEVEL_PACKAGE_DEPENDS "opencl-headers (>= 2.2~0), level-zero(=${PROJECT_VERSION})")
    set(CPACK_DEB_COMPONENT_INSTALL ON)
    set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
endif()

INCLUDE(CPack)
