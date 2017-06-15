cmake_minimum_required(VERSION 3.6)
project(Extlib_SuperBuild)

include(ExternalProject)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(NOT DEFINED EXTLIB_INSTALL_PREFIX)
        set(EXTLIB_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/Install")
    endif()    
    set(CMAKE_INSTALL_PREFIX "${EXTLIB_INSTALL_PREFIX}" CACHE PATH "Install Path" FORCE)
    # message("ZZZZZZZZZZZZZZZZZZZ")
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

if (NOT CMAKE_CONFIGURATION_TYPES)
    if(NOT CMAKE_BUILD_TYPE)
        if(NOT DEFINED EXTLIB_BUILD_TYPE)
            set(EXTLIB_BUILD_TYPE "Release")
        endif()
        set(CMAKE_BUILD_TYPE ${EXTLIB_BUILD_TYPE} CACHE STRING "Choose Extlib Build Type" FORCE)
        set(PROPERTY CACHE CMAKE_BUILD_TYPE
            PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelwithDebInfo" )
        message("CMake hasnt set build type")
    else()
        # set(EXTLIB_BUILD_TYPE ${CMAKE_BUILD_TYPE})
        message("CMake already set build type ${CMAKE_BUILD_TYPE}")
    endif()
    # message("ASDFSDFSDFSDFSDFSDFSDFSDFSDFSDFSDFSDF")
endif()

option(BUILD_PROGSCHJ "Build progschj examples" OFF)

set(ALL_PROJECT_DIR "${CMAKE_BINARY_DIR}/Projects")
set(FREEGLUT_PROJECT_DIR "${ALL_PROJECT_DIR}/FreeGLUT")
set(GLEW_PROJECT_DIR "${ALL_PROJECT_DIR}/GLEW")
set(GLFW_PROJECT_DIR "${ALL_PROJECT_DIR}/GLFW")
set(FLTK_PROJECT_DIR "${ALL_PROJECT_DIR}/FLTK")
# set(GLAD_PROJECT_DIR "${ALL_PROJECT_DIR}/GLAD")
set(FREEIMAGE_PROJECT_DIR "${ALL_PROJECT_DIR}/FreeImage")
set(GLI_PROJECT_DIR "${ALL_PROJECT_DIR}/GLI")
set(GLM_PROJECT_DIR "${ALL_PROJECT_DIR}/GLM")
set(ASSIMP_PROJECT_DIR "${ALL_PROJECT_DIR}/ASSIMP")
set(KTXTOOL_PROJECT_DIR "${ALL_PROJECT_DIR}/KTXtool")
set(PROGSCHJ_EXAMPLES_PROJECT_DIR "${ALL_PROJECT_DIR}/ProgschjExamples")
# set(GLO_PROJECT_DIR "${ALL_PROJECT_DIR}/GLO")

set(LOCAL_PROJECT_DIR "${CMAKE_BINARY_DIR}/Local")
set(SQLITE_LOCAL_DIR "${CMAKE_SOURCE_DIR}/sqlite-amalgamation-3180000")
set(SQLITE_PROJECT_DIR "${LOCAL_PROJECT_DIR}/SQLite")
#[[ if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(PICOPIXELCLIENT_LOCAL_DIR "${CMAKE_SOURCE_DIR}/pico-pixel-client-sdk-master")
    set(PICOPIXELCLIENT_PROJECT_DIR "${LOCAL_PROJECT_DIR}/PicoPixelClient")
endif() #]]

set(EXTLIB_TARGETS)

ExternalProject_Add(SQLite
    DOWNLOAD_COMMAND ""

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    PREFIX "${SQLITE_PROJECT_DIR}"
    SOURCE_DIR "${SQLITE_LOCAL_DIR}"
    BINARY_DIR "${SQLITE_PROJECT_DIR}/build"
    TMP_DIR "${SQLITE_PROJECT_DIR}/temp"
    STAMP_DIR "${SQLITE_PROJECT_DIR}/stamp"
)

list(APPEND EXTLIB_TARGETS SQLite)

#[[ if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows") # PicoPixel client includes window specific headers
    ExternalProject_Add(PicoPixelClient
        DOWNLOAD_COMMAND ""

        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

        PREFIX ${PICOPIXELCLIENT_PROJECT_DIR}
        SOURCE_DIR ${PICOPIXELCLIENT_LOCAL_DIR}
        BINARY_DIR "${PICOPIXELCLIENT_PROJECT_DIR}/build"
        TMP_DIR "${PICOPIXELCLIENT_PROJECT_DIR}/temp"
        STAMP_DIR "${PICOPIXELCLIENT_PROJECT_DIR}/stamp"
    )

    list(APPEND EXTLIB_TARGETS PicoPixelClient)
    message(STATUS "PicoPixelClient is added")
endif()    #]]

# Get FreeGLUT 3.0.0
ExternalProject_Add(FreeGLUT
    GIT_REPOSITORY "https://github.com/dcnieho/FreeGLUT.git"
    GIT_TAG "cd8bf6e3ae9913f004ee55c7c02743e601ab9411"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
    
    PATCH_COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/freeglut/CMakeLists.txt"
        "<SOURCE_DIR>/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/freeglut/freeglutConfig.cmake.in"
        "<SOURCE_DIR>/freeglutConfig.cmake.in"

    PREFIX ${FREEGLUT_PROJECT_DIR}
    BINARY_DIR "${FREEGLUT_PROJECT_DIR}/build"
    TMP_DIR "${FREEGLUT_PROJECT_DIR}/temp"
    STAMP_DIR "${FREEGLUT_PROJECT_DIR}/stamp"
)

list(APPEND EXTLIB_TARGETS FreeGLUT)

ExternalProject_Add(GLEW
    URL "${CMAKE_SOURCE_DIR}/glew-1.13.0.tgz"
    URL_MD5 7cbada3166d2aadfc4169c4283701066

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    PATCH_COMMAND ${CMAKE_COMMAND} -E echo "Patching GLEW..."
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "<SOURCE_DIR>/build/cmake/"
        "<SOURCE_DIR>"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/glew/CMakeLists.txt" 
        "<SOURCE_DIR>/CMakeLists.txt"

    PREFIX "${GLEW_PROJECT_DIR}"
    BINARY_DIR "${GLEW_PROJECT_DIR}/build"
    TMP_DIR "${GLEW_PROJECT_DIR}/temp"
    STAMP_DIR "${GLEW_PROJECT_DIR}/stamp"
)

list(APPEND EXTLIB_TARGETS GLEW)

if(BUILD_PROGSCHJ)
    ExternalProject_Add(ProgschjExamples
        GIT_REPOSITORY "https://github.com/progschj/OpenGL-Examples.git"
        GIT_TAG "dd74a51ec081ad8584bdba023f367f33b5add66a"

        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

        PREFIX ${PROGSCHJ_EXAMPLES_PROJECT_DIR}
        BINARY_DIR "${PROGSCHJ_EXAMPLES_PROJECT_DIR}/build"
        TMP_DIR "${PROGSCHJ_EXAMPLES_PROJECT_DIR}/temp"
        STAMP_DIR "${PROGSCHJ_EXAMPLES_PROJECT_DIR}/stamp"
    )

    list(APPEND EXTLIB_TARGETS ProgschjExamples)
endif(BUILD_PROGSCHJ)

ExternalProject_Add(GLFW
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "488423236053d988f2b1f4b55e64bccbfce9abcb"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    PREFIX ${GLFW_PROJECT_DIR}
    BINARY_DIR "${GLFW_PROJECT_DIR}/build"
    TMP_DIR "${GLFW_PROJECT_DIR}/temp"
    STAMP_DIR "${GLFW_PROJECT_DIR}/stamp"
)

list(APPEND EXTLIB_TARGETS GLFW)

ExternalProject_Add(FLTK
    URL "${CMAKE_SOURCE_DIR}/fltk-1.3.4-1-source.tar.gz"
    URL_MD5 d7fcd27ab928648e1a1366dd2e273970

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    PREFIX "${FLTK_PROJECT_DIR}"
    BINARY_DIR "${FLTK_PROJECT_DIR}/build"
    TMP_DIR "${FLTK_PROJECT_DIR}/temp"
    STAMP_DIR "${FLTK_PROJECT_DIR}/stamp"
)

list(APPEND EXTLIB_TARGETS FLTK)

#[[ ExternalProject_Add(FreeImage
    GIT_REPOSITORY "https://github.com/Kanma/FreeImage.git"
    GIT_TAG "6bb613d9402926b3846dea1b417f20b6c596c5dc"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy 
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/CMakeLists.txt"
       "<SOURCE_DIR>/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/LibMNG/CMakeLists.txt"
       "<SOURCE_DIR>/LibMNG/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/LibOpenJPEG/CMakeLists.txt"
       "<SOURCE_DIR>/LibOpenJPEG/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/LibPNG/CMakeLists.txt"
       "<SOURCE_DIR>/LibPNG/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/LibJPEG/CMakeLists.txt"
       "<SOURCE_DIR>/LibJPEG/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/LibRawLite/CMakeLists.txt"
       "<SOURCE_DIR>/LibRawLite/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/OpenEXR/CMakeLists.txt"
       "<SOURCE_DIR>/OpenEXR/CMakeLists.txt"      
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/CompilerTypeFix.cmake"
       "<SOURCE_DIR>/CompilerTypeFix.cmake"
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/dependencies/XMake/XMake.cmake"
       "<SOURCE_DIR>/dependencies/XMake/XMake.cmake"      
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/freeimage-config.cmake"
       "<SOURCE_DIR>/freeimage-config.cmake"   
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/FreeImage/PluginTIFF.cpp"
       "<SOURCE_DIR>/FreeImage/PluginTIFF.cpp"   
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/LibTIFF/CMakeLists.txt"
       "<SOURCE_DIR>/LibTIFF/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/patch/FreeImage/dependencies/zlib/CMakeLists.txt"
       "<SOURCE_DIR>/dependencies/zlib/CMakeLists.txt"

    PREFIX ${FREEIMAGE_PROJECT_DIR}
    BINARY_DIR "${FREEIMAGE_PROJECT_DIR}/build"
    TMP_DIR "${FREEIMAGE_PROJECT_DIR}/temp"
    STAMP_DIR "${FREEIMAGE_PROJECT_DIR}/stamp"
) #]]

ExternalProject_Add(GLI
    GIT_REPOSITORY "https://github.com/g-truc/gli.git"
    GIT_TAG "7da5f50931225e9819a26d5cb323c5f42da50bcd"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    PREFIX ${GLI_PROJECT_DIR}
    BINARY_DIR "${GLI_PROJECT_DIR}/build"
    TMP_DIR "${GLI_PROJECT_DIR}/temp"
    STAMP_DIR "${GLI_PROJECT_DIR}/stamp"
)

list(APPEND EXTLIB_TARGETS GLI)

ExternalProject_Add(GLM
    GIT_REPOSITORY "https://github.com/g-truc/glm.git"
    GIT_TAG "40398d67cd3e4f74b08649eda428dc411d801fd5"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    PREFIX ${GLM_PROJECT_DIR}
    BINARY_DIR "${GLM_PROJECT_DIR}/build"
    TMP_DIR "${GLM_PROJECT_DIR}/temp"
    STAMP_DIR "${GLM_PROJECT_DIR}/stamp"
)

list(APPEND EXTLIB_TARGETS GLM)

#[[ ExternalProject_Add(ASSIMP
    GIT_REPOSITORY "https://github.com/assimp/assimp.git"
    GIT_TAG "51520cb5f1adcb588a2533d450aace480c7cc3d4"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    PREFIX ${ASSIMP_PROJECT_DIR}
    BINARY_DIR "${ASSIMP_PROJECT_DIR}/build"
    TMP_DIR "${ASSIMP_PROJECT_DIR}/temp"
    STAMP_DIR "${ASSIMP_PROJECT_DIR}/stamp"
) 

list(APPEND EXTLIB_TARGETS ASSIMP) #]]

#[[ ExternalProject_Add(GLO
    GIT_REPOSITORY "https://github.com/g-truc/glo.git"
    GIT_TAG "e5736d57b8a5caad8647360f6efe0ddfb62de2ae"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    PREFIX ${GLO_PROJECT_DIR}
    BINARY_DIR "${GLO_PROJECT_DIR}/build"
    TMP_DIR "${GLO_PROJECT_DIR}/temp"
    STAMP_DIR "${GLO_PROJECT_DIR}/stamp"
) #]]


#[[ ExternalProject_Add(GLAD
    GIT_REPOSITORY "https://github.com/Dav1dde/glad.git"
    GIT_TAG "4014836cb06e86058b1e82b4b1777f511e31ef11"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
               -DGLAD_INSTALL:BOOL=ON

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/GLAD/CMakeLists.txt"
        "<SOURCE_DIR>/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/GLAD/GLADConfig.cmake"
        "<SOURCE_DIR>/GLADConfig.cmake"

    PREFIX "${GLAD_PROJECT_DIR}"
    BINARY_DIR "${GLAD_PROJECT_DIR}/build"
    TMP_DIR "${GLAD_PROJECT_DIR}/temp"
    STAMP_DIR "${GLAD_PROJECT_DIR}/stamp"
) #]]

ExternalProject_Get_Property(GLEW SOURCE_DIR)
set(GLEW_INCLUDE_DIR "${SOURCE_DIR}/include")

ExternalProject_Get_Property(FreeGLUT BINARY_DIR)
set(FreeGLUT_DIR ${BINARY_DIR})

ExternalProject_Get_Property(FLTK BINARY_DIR)
set(FLTK_DIR ${BINARY_DIR})

ExternalProject_Get_Property(GLFW BINARY_DIR)
set(GLFW_DIR ${BINARY_DIR})

include("cmake/CompilerSettings.cmake")
include("cmake/WriteInitialCache.cmake")

# SET(ABC "C:/Program Files (x86)")
ExtlibWriteConfig(
    OUTPUT_FILE "${CMAKE_BINARY_DIR}/TempCache.txt"
    CMAKE_CACHE_ARGS

        ${EXTLIB_COMPILER_ARGS}

        -DEXTLIB_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DEXTLIB_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -DEXTLIB_GENERATOR:STRING=${CMAKE_GENERATOR}

        -DFREEGLUT_DIR:PATH=${FreeGLUT_DIR}
        # -DGLEW_INCLUDE_DIR:PATH=${GLEW_INCLUDE_DIR}
        -DGLEW_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/glew
        -Dglfw3_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/glfw3
        -DFLTK_DIR:PATH=${CMAKE_INSTALL_PREFIX}/CMake
        -DSQLite_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/SQLite
        -DGLI_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/gli
        -DGLM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/glm

#        -DTEST_ABC:PATH=${ABC}
)

add_custom_command(OUTPUT "${CMAKE_BINARY_DIR}/ExtlibCache.txt"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/TempCache.txt" "${CMAKE_BINARY_DIR}/ExtlibCache.txt"
    DEPENDS "${CMAKE_BINARY_DIR}/TempCache.txt"
    COMMENT "Generating ExtlibCache.txt"
)

add_custom_target(ExtlibCache ALL
    # COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/ExtlibCache.txt"
    # COMMAND ${CMAKE_COMMAND} -E rename "${CMAKE_BINARY_DIR}/TempCache.txt" "${CMAKE_BINARY_DIR}/ExtlibCache.txt"
    DEPENDS ${EXTLIB_TARGETS} "${CMAKE_BINARY_DIR}/ExtlibCache.txt"
)

message("Current Generator is ${CMAKE_GENERATOR}")