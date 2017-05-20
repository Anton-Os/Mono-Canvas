# List the header files
set(HEADERS internal/defines.h
            internal/libraw_internal_funcs.h
            internal/var_defines.h
            libraw/libraw.h
            libraw/libraw_alloc.h
            libraw/libraw_const.h
            libraw/libraw_datastream.h
            libraw/libraw_internal.h
            libraw/libraw_types.h
            libraw/libraw_version.h
)


# List the source files
set(SRCS src/libraw_c_api.cpp
         src/libraw_cxx.cpp
         internal/dcraw_common.cpp
         internal/dcraw_fileio.cpp
)

# List the include paths
# include_directories(.)

# Declaration of the library
xmake_create_static_library(RAWLITE rawlite ${HEADERS} ${SRCS})

# ---------- START

target_include_directories(rawlite PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/FreeImage>
)

if (WIN32)
    # ntohl... need we2_32 on Windows
    target_link_libraries(rawlite PUBLIC ws2_32)
endif (WIN32)

xmake_install_target(rawlite)

install(FILES ${HEADERS}
    DESTINATION include/FreeImage/libraw
)

# ---------- FINISH

xmake_add_to_list_property(RAWLITE COMPILE_DEFINITIONS "LIBRAW_NODLL;LIBRAW_LIBRARY_BUILD;NO_LCMS")

include("${CMAKE_SOURCE_DIR}/CompilerTypeFix.cmake")
fixCompilerType(RAWLITE)
