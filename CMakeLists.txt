# Copyright (C) 2020-2021 Intel Corporation
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC AND (MSVC_VERSION LESS 1900))
    message(FATAL_ERROR "Visual Studio Compiler Version >= 1900 Required to build.")
endif()

# This project follows semantic versioning (https://semver.org/). Only set the
# major and minor version here - patch version is determined dynamically.
project(level-zero VERSION 1.4)

# Patch version corresponds to # of commits on master since last version
# major/minor tag (e.g., v1.0). If not building in a git repository, then get
# the patch version from a VERSION_PATCH file that would be shipped with a
# source distribution. Otherwise, use 0.
set(PROJECT_VERSION_PATCH 0)
find_package(Git)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION_PATCH")
	file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION_PATCH" VERSION_PATCH)
	string(STRIP "${VERSION_PATCH}" PROJECT_VERSION_PATCH)
	message(STATUS "Using patch version from VERSION_PATCH file in source tree: ${PROJECT_VERSION_PATCH}")
elseif(Git_FOUND)
	if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
		message(WARNING "Cannot determine patch version - VERSION_PATCH file is not in source tree and source tree does not appear to be a git repository. Using 0 as patch version.")
		set(PROJECT_VERSION_PATCH 0)
	else()
		set(GIT_TAG "v${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
		if(MSVC)
			set(grep_string \\[CI\\] )
			execute_process(
				COMMAND CMD /c ${GIT_EXECUTABLE} rev-list ${GIT_TAG}..HEAD --grep=${grep_string} --invert-grep --count
				OUTPUT_VARIABLE VERSION_PATCH
				WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			)
		else()
			set(grep_string "\\[CI\\] ")
			execute_process(
				COMMAND ${GIT_EXECUTABLE} rev-list ${GIT_TAG}..HEAD --grep=${grep_string} --invert-grep --count
				OUTPUT_VARIABLE VERSION_PATCH
				WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			)
		endif()
		string(STRIP "${VERSION_PATCH}" PROJECT_VERSION_PATCH)
		if(PROJECT_VERSION_PATCH STREQUAL "")
			message(WARNING "Cannot determine patch version - couldn't find ${GIT_TAG} tag in repository. Using 0 as patch version.")
			set(PROJECT_VERSION_PATCH 0)
		else()
			message(STATUS "Using patch version from commit count in git repository: ${PROJECT_VERSION_PATCH}")
		endif()
	endif()
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
    # enable Spectre Mitigation
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qspectre")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Qspectre")
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
    
    # enable creation of PDB files for Release Builds
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/wrapper/include)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(TARGET_LOADER_NAME ze_loader)


add_subdirectory(source)
add_subdirectory(samples)

include("os_release_info.cmake")
get_os_release_info(os_name os_version os_codename)
string(APPEND os_type "${os_name}")
string(COMPARE EQUAL "${os_type}" "sles" sles_distro)
#Pick only first character of os_name
string(SUBSTRING "${os_name}" 0 1 os_name)

file(GLOB LEVEL_ZERO_API_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

install(FILES ${LEVEL_ZERO_API_HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/level_zero/
    COMPONENT level-zero-devel
)

file(GLOB LEVEL_ZERO_LAYERS_API_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/layers/*.h")

install(FILES ${LEVEL_ZERO_LAYERS_API_HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/level_zero/layers
    COMPONENT level-zero-devel
)

file(GLOB LEVEL_ZERO_LOADER_API_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/loader/*.h")

install(FILES ${LEVEL_ZERO_LOADER_API_HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/level_zero/loader
    COMPONENT level-zero-devel
)

# If generators list was not define build native package for current distro
if(NOT DEFINED CPACK_GENERATOR)
	if(EXISTS "/etc/debian_version")
		set(CPACK_GENERATOR "DEB")
	elseif(EXISTS "/etc/redhat-release")
		set(CPACK_GENERATOR "RPM")
	elseif(EXISTS "/etc/SUSE-brand" OR EXISTS "/etc/SUSE-release" OR sles_distro)
		set(CPACK_GENERATOR "RPM")
	else()
		set(CPACK_GENERATOR "ZIP")
	endif()
endif()

if(MSVC)
	set(CPACK_SET_DESTDIR FALSE)
	set(CPACK_PACKAGING_INSTALL_PREFIX "")
	install(DIRECTORY "${CMAKE_INSTALL_PREFIX}/include/" DESTINATION "include")
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
	set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
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
	set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
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
