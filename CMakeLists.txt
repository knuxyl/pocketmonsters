# Compatibility
cmake_minimum_required(VERSION 3.23)
# Check if environment can build project
project(pmcg)
# Cmake features
include(ExternalProject)
# Project defined cmake options
cmake_policy(SET CMP0144 NEW)
cmake_policy(SET CMP0167 NEW)
set(DEP_INSTALL_DIR "${CMAKE_SOURCE_DIR}/external/install")
set(DEP_BUILD_DIR "${CMAKE_SOURCE_DIR}/external/build")
set(CMAKE_PREFIX_PATH "${DEP_INSTALL_DIR}" ${CMAKE_PREFIX_PATH})
# User defined and defaulted cmake options
option(PMCG_SOFTWARE_RENDERER "Build game with software rendering" OFF)
option(UPDATE_DEPS "Update external sources" OFF)
option(BUILD_DEPS "Rebuild dependencies (builds if not built)" OFF)
option(CMAKE_BUILD_TYPE "Set optimization level")
option(PMCG_RAYLIB "Rebuild raylib" OFF)
if(BUILD_DEPS)
	file(REMOVE_RECURSE "${DEP_INSTALL_DIR}")
	file(REMOVE_RECURSE "${DEP_BUILD_DIR}")
endif()
include(cmake/cbor.cmake)
include(cmake/sodium.cmake)
include(cmake/gpg-error.cmake)
include(cmake/gcrypt.cmake)
include(cmake/usb.cmake)
include(cmake/hidapi.cmake)
include(cmake/gme.cmake)
include(cmake/flac.cmake)
include(cmake/ogg.cmake)
include(cmake/opus.cmake)
include(cmake/opusfile.cmake)
include(cmake/sdl.cmake)
include(cmake/raylib.cmake)
include(cmake/zint.cmake)
include(cmake/zxing.cmake)
include(cmake/xml2.cmake)
include(cmake/tmx.cmake)
#include(cmake/boost.cmake)
#include(cmake/rime.cmake)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message("Target OS: Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message("Target OS: Linux")
    #include(cmake/alsa.cmake)
    include(cmake/drm.cmake)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message("Target OS: macOS")
endif()
#--------------------------------------#
#
#	Final build steps
#
#--------------------------------------#
# Create a target to hold properties
add_executable(pmcg)
# Add dependencies so they are built first
#libusb libhidapi libdrm alsa-lib 
add_dependencies(pmcg xml2 tmx gpg-error gcrypt sodium cbor gme zxing sdl raylib)
# Add projects to executable
# usb hidapi-libusb drm atopology alsa 
target_link_libraries(pmcg PRIVATE xml2 tmx zxing gpg-error gcrypt sodium cbor gme sdl raylib stdc++ m)
# Add include dir
target_include_directories(pmcg PRIVATE "${DEP_INSTALL_DIR}/include" "${DEP_INSTALL_DIR}/include/libdrm" "${CMAKE_SOURCE_DIR}/external/clay" "${CMAKE_SOURCE_DIR}/external/clay/renderers")
# Add source files property to target
# PRIVATE because no other target will depend on the executable
target_sources(pmcg PRIVATE src/main.c)
