cmake_minimum_required(VERSION 3.6)
project(Extlib_SuperBuild)

include(ExternalProject)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(NOT DEFINED EXTLIB_INSTALL_PREFIX)
        set(EXTLIB_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/Install")
    endif()    
    set(CMAKE_INSTALL_PREFIX "${EXTLIB_INSTALL_PREFIX}" CACHE PATH "Install Path" FORCE)
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
        message("CMake already set build type ${CMAKE_BUILD_TYPE}")
    endif()
endif()

option(BUILD_PROGSCHJ "Build progschj examples" OFF)

set(PYTHON_EMBEDDED_DIR "${CMAKE_SOURCE_DIR}/python-3.6.1-embed")

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
set(PROGSCHJ_EXAMPLES_PROJECT_DIR "${ALL_PROJECT_DIR}/ProgschjExamples")
set(GOOGLETEST_PROJECT_DIR "${ALL_PROJECT_DIR}/GoogleTest")
set(GLSLANG_PROJECT_DIR "${ALL_PROJECT_DIR}/GLSLang")
set(SPIRVTOOLS_PROJECT_DIR "${ALL_PROJECT_DIR}/SPIRV_Tools")
set(SPIRVHEADERS_PROJECT_DIR "${ALL_PROJECT_DIR}/SPIRV_Headers")
set(SHADERC_PROJECT_DIR "${ALL_PROJECT_DIR}/ShaderC")
set(EIGEN_PROJECT_DIR "${ALL_PROJECT_DIR}/Eigen")
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

ExternalProject_Add(ASSIMP
    GIT_REPOSITORY "https://github.com/assimp/assimp.git"
    GIT_TAG "b38ba233f530fdb103d3ede3df5126121af78b10"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/Assimp/code/CMakeLists.txt"
        "<SOURCE_DIR>/code/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/Assimp/assimp-config.cmake"
        "<SOURCE_DIR>/assimp-config.cmake"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/Assimp/contrib/zlib/CMakeLists.txt"
        "<SOURCE_DIR>/contrib/zlib/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/Assimp/contrib/zlib/zlib-config.cmake"
        "<SOURCE_DIR>/zlib-config.cmake"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/Assimp/contrib/irrXML/CMakeLists.txt"
        "<SOURCE_DIR>/contrib/irrXML/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/Assimp/contrib/irrXML/irrxml-config.cmake"
        "<SOURCE_DIR>/irrxml-config.cmake"

    PREFIX ${ASSIMP_PROJECT_DIR}
    BINARY_DIR "${ASSIMP_PROJECT_DIR}/build"
    TMP_DIR "${ASSIMP_PROJECT_DIR}/temp"
    STAMP_DIR "${ASSIMP_PROJECT_DIR}/stamp"
) 

list(APPEND EXTLIB_TARGETS ASSIMP)

ExternalProject_Add(GoogleTest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "4bab34d2084259cba67f3bfb51217c10d606e175"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""

    PREFIX ${GOOGLETEST_PROJECT_DIR}
    BINARY_DIR "${GOOGLETEST_PROJECT_DIR}/build"
    TMP_DIR "${GOOGLETEST_PROJECT_DIR}/temp"
    STAMP_DIR "${GOOGLETEST_PROJECT_DIR}/stamp"
)

list(APPEND EXTLIB_TARGETS GoogleTest)

ExternalProject_Add(Glslang
    GIT_REPOSITORY "https://github.com/KhronosGroup/glslang.git"
    GIT_TAG "9645f78293a59780b06ba93938bc46850b2c5b3c"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""

    PREFIX ${GLSLANG_PROJECT_DIR}
    BINARY_DIR "${GLSLANG_PROJECT_DIR}/build"
    TMP_DIR "${GLSLANG_PROJECT_DIR}/temp"
    STAMP_DIR "${GLSLANG_PROJECT_DIR}/stamp"
)

list(APPEND EXTLIB_TARGETS Glslang)

ExternalProject_Add(SPIRV_Tools
    GIT_REPOSITORY "https://github.com/KhronosGroup/SPIRV-Tools.git"
    GIT_TAG "35a06958441b68a74c9a817b33bba110b385d5f4"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/SPIRV_Tools/CMakeLists.txt"
        "<SOURCE_DIR>/CMakeLists.txt"

    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""

    PREFIX ${SPIRVTOOLS_PROJECT_DIR}
    BINARY_DIR "${SPIRVTOOLS_PROJECT_DIR}/build"
    TMP_DIR "${SPIRVTOOLS_PROJECT_DIR}/temp"
    STAMP_DIR "${SPIRVTOOLS_PROJECT_DIR}/stamp"
)

list(APPEND EXTLIB_TARGETS SPIRV_Tools)

ExternalProject_Get_Property(SPIRV_Tools SOURCE_DIR)
set(SHADERC_SPIRVTOOLS_DIR ${SOURCE_DIR})
set(SHADERC_SPIRVTOOLS_INCLUDE_DIR "${SHADERC_SPIRVTOOLS_DIR}/include")

ExternalProject_Add(SPIRV_Headers
    GIT_REPOSITORY "https://github.com/KhronosGroup/SPIRV-Headers.git"
    GIT_TAG "661ad91124e6af2272afd00f804d8aa276e17107"

    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""

    PREFIX ${SPIRVHEADERS_PROJECT_DIR}
    BINARY_DIR "${SPIRVHEADERS_PROJECT_DIR}/build"
    TMP_DIR "${SPIRVHEADERS_PROJECT_DIR}/temp"
    STAMP_DIR "${SPIRVHEADERS_PROJECT_DIR}/stamp"

    SOURCE_DIR "${SHADERC_SPIRVTOOLS_DIR}/external/spirv-headers"
    DEPENDS SPIRV_Tools
)

list(APPEND EXTLIB_TARGETS SPIRV_Headers)

ExternalProject_Get_Property(GoogleTest SOURCE_DIR)
set(SHADERC_GOOGLETEST_DIR ${SOURCE_DIR})

ExternalProject_Get_Property(Glslang SOURCE_DIR)
set(SHADERC_GLSLANG_DIR ${SOURCE_DIR})

ExternalProject_Add(ShaderC
    GIT_REPOSITORY "https://github.com/google/shaderc.git"
    GIT_TAG "41ce8e69e12b3fe8370e9d49e1760ea711d5e61b"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
               -DSHADERC_GOOGLE_TEST_DIR:PATH=${SHADERC_GOOGLETEST_DIR}
               -DSHADERC_GLSLANG_DIR:PATH=${SHADERC_GLSLANG_DIR}
               -DSHADERC_SPIRV_TOOLS_DIR:PATH=${SHADERC_SPIRVTOOLS_DIR}
               -DPYTHON_EXE:FILEPATH=${PYTHON_EMBEDDED_DIR}/python.exe

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/ShaderC/third_party/CMakeLists.txt"
        "<SOURCE_DIR>/third_party/CMakeLists.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/patch/ShaderC/CMakeLists.txt"
        "<SOURCE_DIR>/CMakeLists.txt"

    PREFIX ${SHADERC_PROJECT_DIR}
    BINARY_DIR "${SHADERC_PROJECT_DIR}/build"
    TMP_DIR "${SHADERC_PROJECT_DIR}/temp"
    STAMP_DIR "${SHADERC_PROJECT_DIR}/stamp"

    DEPENDS GoogleTest Glslang SPIRV_Tools SPIRV_Headers
)

list(APPEND EXTLIB_TARGETS ShaderC)

#[[ ExternalProject_Add(Eigen
    GIT_REPOSITORY "https://github.com/PX4/eigen.git"
    GIT_TAG "e7850ed81f9c469e02df496ef09ae32ec0379b71"

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}

    PREFIX ${EIGEN_PROJECT_DIR}
    BINARY_DIR "${EIGEN_PROJECT_DIR}/build"
    TMP_DIR "${EIGEN_PROJECT_DIR}/temp"
    STAMP_DIR "${EIGEN_PROJECT_DIR}/stamp"

    DEPENDS GoogleTest Glslang SPIRV_Tools SPIRV_Headers
)

list(APPEND EXTLIB_TARGETS Eigen) #]]

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

include("cmake/CompilerSettings.cmake")
include("cmake/WriteInitialCache.cmake")

ExtlibWriteConfig(
    OUTPUT_FILE "${CMAKE_BINARY_DIR}/TempCache.txt"
    CMAKE_CACHE_ARGS

        ${EXTLIB_COMPILER_ARGS}

        -DEXTLIB_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DEXTLIB_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -DEXTLIB_GENERATOR:STRING=${CMAKE_GENERATOR}

        -Dfreeglut_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT
        -DGLEW_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/glew
        -Dglfw3_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/glfw3
        -DFLTK_DIR:PATH=${CMAKE_INSTALL_PREFIX}/CMake
        -DSQLite_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/SQLite
        -DGLI_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/gli
        -DGLM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/glm
        -DASSIMP_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-3.3

)

add_custom_command(OUTPUT "${CMAKE_BINARY_DIR}/ExtlibCache.txt"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/TempCache.txt" "${CMAKE_BINARY_DIR}/ExtlibCache.txt"
    DEPENDS "${CMAKE_BINARY_DIR}/TempCache.txt"
    COMMENT "Generating ExtlibCache.txt"
)

add_custom_target(ExtlibCache ALL
        DEPENDS ${EXTLIB_TARGETS} "${CMAKE_BINARY_DIR}/ExtlibCache.txt"
)

message("Current Generator is ${CMAKE_GENERATOR}")

if(IS_DIRECTORY "${CMAKE_BINARY_DIR}/SPIRV_Headers-prefix")
    file(REMOVE
        "${CMAKE_BINARY_DIR}/SPIRV_Headers-prefix"
    )
endif()