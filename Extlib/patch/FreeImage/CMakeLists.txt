cmake_minimum_required(VERSION 2.6)
project(FREEIMAGE)


##########################################################################################
# XMake-related settings

# Set the output paths
if (NOT DEFINED XMAKE_BINARY_DIR)
    set(XMAKE_BINARY_DIR "${FREEIMAGE_BINARY_DIR}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/bin")
endif()

# Set the dependencies path
if (NOT DEFINED XMAKE_DEPENDENCIES_DIR)
    set(XMAKE_DEPENDENCIES_DIR "${FREEIMAGE_SOURCE_DIR}/dependencies")
endif()


##########################################################################################
# XMake importation

if (NOT EXISTS "${XMAKE_DEPENDENCIES_DIR}/XMake/XMake.cmake")
    message(FATAL_ERROR
"Missing dependency: XMake
This distribution of FreeImage requires the following dependencies:
   - XMake
   - ZLib
They are provided as GIT submodules of this repository.
Did you forgot to execute the following commands?
   git submodule init
   git submodule update")
endif()

include("${XMAKE_DEPENDENCIES_DIR}/XMake/XMake.cmake")


##########################################################################################
# Process subdirectories

add_subdirectory(dependencies)
add_subdirectory(LibJPEG)
add_subdirectory(LibMNG)
add_subdirectory(LibOpenJPEG)
add_subdirectory(LibPNG)
add_subdirectory(LibRawLite)
add_subdirectory(LibTIFF)
add_subdirectory(OpenEXR)


##########################################################################################
# Declaration of the library

# List the header files
set(HEADERS CacheFile.h
            FreeImage.h
            FreeImageIO.h
            Plugin.h
            Quantizers.h
            ToneMapping.h
            Utilities.h
            FreeImage/PSDParser.h
            FreeImageToolkit/Filters.h
            FreeImageToolkit/Resize.h
            Metadata/FIRational.h
            Metadata/FreeImageTag.h
)

# List the source files
set(SRCS FreeImage/BitmapAccess.cpp
         FreeImage/CacheFile.cpp
         FreeImage/ColorLookup.cpp
         FreeImage/Conversion.cpp
         FreeImage/Conversion16_555.cpp
         FreeImage/Conversion16_565.cpp
         FreeImage/Conversion24.cpp
         FreeImage/Conversion32.cpp
         FreeImage/Conversion4.cpp
         FreeImage/Conversion8.cpp
         FreeImage/ConversionRGBF.cpp
         FreeImage/ConversionType.cpp
         FreeImage/FreeImage.cpp
         FreeImage/FreeImageIO.cpp
         FreeImage/GetType.cpp
         FreeImage/Halftoning.cpp
         FreeImage/J2KHelper.cpp
         FreeImage/MemoryIO.cpp
         FreeImage/MultiPage.cpp
         FreeImage/NNQuantizer.cpp
         FreeImage/PSDParser.cpp
         FreeImage/PixelAccess.cpp
         FreeImage/Plugin.cpp
         FreeImage/PluginBMP.cpp
         FreeImage/PluginCUT.cpp
         FreeImage/PluginDDS.cpp
         FreeImage/PluginEXR.cpp
         FreeImage/PluginG3.cpp
         FreeImage/PluginGIF.cpp
         FreeImage/PluginHDR.cpp
         FreeImage/PluginICO.cpp
         FreeImage/PluginIFF.cpp
         FreeImage/PluginJ2K.cpp
         FreeImage/PluginJP2.cpp
         FreeImage/PluginJPEG.cpp
         FreeImage/PluginKOALA.cpp
         FreeImage/PluginMNG.cpp
         FreeImage/PluginPCD.cpp
         FreeImage/PluginPCX.cpp
         FreeImage/PluginPFM.cpp
         FreeImage/PluginPICT.cpp
         FreeImage/PluginPNG.cpp
         FreeImage/PluginPNM.cpp
         FreeImage/PluginPSD.cpp
         FreeImage/PluginRAS.cpp
         FreeImage/PluginRAW.cpp
         FreeImage/PluginSGI.cpp
         FreeImage/PluginTARGA.cpp
         FreeImage/PluginTIFF.cpp
         FreeImage/PluginWBMP.cpp
         FreeImage/PluginXBM.cpp
         FreeImage/PluginXPM.cpp
         FreeImage/TIFFLogLuv.cpp
         FreeImage/ToneMapping.cpp
         FreeImage/WuQuantizer.cpp
         FreeImage/ZLibInterface.cpp
         FreeImage/tmoColorConvert.cpp
         FreeImage/tmoDrago03.cpp
         FreeImage/tmoFattal02.cpp
         FreeImage/tmoReinhard05.cpp
         FreeImageToolkit/BSplineRotate.cpp
         FreeImageToolkit/Background.cpp
         FreeImageToolkit/Channels.cpp
         FreeImageToolkit/ClassicRotate.cpp
         FreeImageToolkit/Colors.cpp
         FreeImageToolkit/CopyPaste.cpp
         FreeImageToolkit/Display.cpp
         FreeImageToolkit/Flip.cpp
         FreeImageToolkit/JPEGTransform.cpp
         FreeImageToolkit/MultigridPoissonSolver.cpp
         FreeImageToolkit/Rescale.cpp
         FreeImageToolkit/Resize.cpp
         Metadata/Exif.cpp
         Metadata/FIRational.cpp
         Metadata/FreeImageTag.cpp
         Metadata/IPTC.cpp
         Metadata/TagConversion.cpp
         Metadata/TagLib.cpp
         Metadata/XTIFF.cpp
)

# List the include paths
include_directories(${FREEIMAGE_SOURCE_DIR}
                    ${FREEIMAGE_SOURCE_DIR}/DeprecationManager
)

xmake_import_search_paths(OPENEXR)
xmake_import_search_paths(ZLIB)

# Declaration of the library
xmake_create_static_library(FREEIMAGE freeimage ${HEADERS} ${SRCS})
xmake_add_to_list_property(FREEIMAGE COMPILE_DEFINITIONS "OPJ_STATIC;FREEIMAGE_LIB;LIBRAW_NODLL")
xmake_add_to_list_property(FREEIMAGE INTERFACE_COMPILE_DEFINITIONS "OPJ_STATIC;FREEIMAGE_LIB;LIBRAW_NODLL")

# ---------- START

target_include_directories(freeimage PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/FreeImage>
)

xmake_install_target(freeimage)

install(FILES ${HEADERS}
    DESTINATION include/FreeImage
)

# ---------- FINISH

include("${CMAKE_SOURCE_DIR}/CompilerTypeFix.cmake")
fixCompilerType(FREEIMAGE)

xmake_project_link(FREEIMAGE JPEG MNG OPENEXR OPENJPEG PNG RAWLITE TIFF ZLIB)

# Exportations
xmake_export_include_paths(FREEIMAGE ${FREEIMAGE_SOURCE_DIR})
xmake_export_compile_definitions(FREEIMAGE "FREEIMAGE_LIB" "OPJ_STATIC" "LIBRAW_NODLL")

install(FILES "${CMAKE_SOURCE_DIR}/freeimage-config.cmake"
        DESTINATION lib/cmake/freeimage
)
