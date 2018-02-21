cmake_minimum_required(VERSION 2.8)
project(PolyArt)

if(NOT EXTLIB_BUILD_PATH)
    set(EXTLIB_BUILD_PATH "${CMAKE_BINARY_DIR}/Extlib-Build" CACHE PATH "Route Exlib Build here")
endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(NOT DEFINED EXTLIB_INSTALL_PREFIX)
        set(EXTLIB_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/Install")
    endif()    
    set(CMAKE_INSTALL_PREFIX "${EXTLIB_INSTALL_PREFIX}" CACHE PATH "Install Path" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    if(NOT DEFINED EXTLIB_BUILD_TYPE)
        set(EXTLIB_BUILD_TYPE "Release")
    endif()
    set(CMAKE_BUILD_TYPE ${EXTLIB_BUILD_TYPE} CACHE STRING "Choose Extlib Build Type" FORCE)
    set(PROPERTY CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelwithDebInfo" )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

set(INSTALL_PREFIX_RUNTIME_DIR "${CMAKE_INSTALL_PREFIX}/bin")
find_program(GLSLC_EXE 
    NAMES glslc
    PATHS ${INSTALL_PREFIX_RUNTIME_DIR}
)

message("Extlib Cache: ${EXTLIB_BUILD_PATH}/ExtlibCache.txt")
message("Current Generator is ${CMAKE_GENERATOR}")
if (EXISTS "${EXTLIB_BUILD_PATH}/ExtlibCache.txt")
    include( "${EXTLIB_BUILD_PATH}/ExtlibCache.txt")
    if(NOT ${CMAKE_GENERATOR} STREQUAL ${EXTLIB_GENERATOR})
        message(FATAL_ERROR "Generators are incompatible")
    endif()

    find_package(Vulkan QUIET MODULE)
    if(Vulkan_FOUND)
        message(STATUS "Vulkan was found")
    endif()

    if(Base_MODULE)
        find_package(GLEW REQUIRED CONFIG)
        find_package(glfw3 REQUIRED CONFIG)
        find_package(GLM REQUIRED CONFIG)
    endif()
    if(Boost_MODULE)
        find_package(Boost REQUIRED)
        
        set(BOOST_LIBS)
        file(GLOB BOOST_LIBS "${BOOST_LIBRARYDIR}/*.lib")
    endif()
    if(Texture_MODULE)
        find_package(GLI REQUIRED CONFIG)
        find_package(stb REQUIRED)
    endif()
    if(Assimp_MODULE)
        find_package(ASSIMP REQUIRED CONFIG)

        # find_library(assimp_lib
        #    NAMES assimp libassimp 
        #    PATH ${ASSIMP_LIBRARY_DIRS}
        # )

        message(STATUS "${ASSIMP_LIBRARIES}")
    endif()
    if(Gui_MODULE)
        find_package(FLTK REQUIRED CONFIG)
    endif()

    # add_subdirectory("Core/v1.0")
    # add_subdirectory("Core/v2.0")
    # add_subdirectory("Core/v2.1")
    # add_subdirectory("Core/v2.2")
    # add_subdirectory("Core/v3.1")
    add_subdirectory("Core/v4.1")
endif()
