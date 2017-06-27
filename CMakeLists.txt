cmake_minimum_required(VERSION 2.8)
project(OpenGL_Mono_Canvas)

if(NOT EXTLIB_BUILD_PATH)
    set(EXTLIB_BUILD_PATH "${CMAKE_BINARY_DIR}/Extlib-Build" CACHE PATH "Route Exlib Build here")
endif()

set(AOPROJ_BUILD_DIR "${CMAKE_BINARY_DIR}/AO")

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

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

message("Extlib Cache: ${EXTLIB_BUILD_PATH}/ExtlibCache.txt")
message("Current Generator is ${CMAKE_GENERATOR}")
if (EXISTS "${EXTLIB_BUILD_PATH}/ExtlibCache.txt")
    include( "${EXTLIB_BUILD_PATH}/ExtlibCache.txt")
    if(NOT ${CMAKE_GENERATOR} STREQUAL ${EXTLIB_GENERATOR})
        message(FATAL_ERROR "Generators are incompatible")
    endif()

    # message(STATUS "Finding Packages")

    find_package(freeglut REQUIRED CONFIG)
    find_package(GLEW REQUIRED CONFIG)
    find_package(glfw3 REQUIRED CONFIG)
    find_package(FLTK CONFIG)
    find_package(SQLite REQUIRED CONFIG)
    find_package(GLI REQUIRED CONFIG)
    find_package(GLM REQUIRED CONFIG)
    # find_package(PicoPixelClient QUIET CONFIG)
    # find_package(FreeImage REQUIRED CONFIG)

    # message(STATUS "FreeGLUT directory ${FREEGLUT_DIR}")

    get_target_property(freeglut_ImportLoc freeglut_static IMPORTED_LOCATION_DEBUG)
    # message(STATUS "FreeGLUT target file ${freeglut_ImportLoc}")

    add_subdirectory("AO/Going3D")
    # add_subdirectory("AO/LevelTwo")
    add_subdirectory("AO/Dimentions")
    add_subdirectory("AO/Triangles_Basis")

else ()
    include("cmake/BuildExtlibs.cmake")
    add_custom_target(BuildExtlibHelp ALL
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan
            "The Project Build Systme is not ready."
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan --no-newline
            "Use "
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --no-newline
            "BuildExtlib "
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan
            "target to build extlib"
      )
endif()
