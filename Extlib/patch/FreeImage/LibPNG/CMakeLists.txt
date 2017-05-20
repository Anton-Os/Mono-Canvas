# List the header files
set(HEADERS png.h
            pngconf.h
)


# List the source files
set(SRCS png.c
         pngerror.c
         #pnggccrd.c
         pngget.c
         pngmem.c
         pngpread.c
         pngread.c
         pngrio.c
         pngrtran.c
         pngrutil.c
         pngset.c
         pngtrans.c
         #pngvcrd.c
         pngwio.c
         pngwrite.c
         pngwtran.c
         pngwutil.c
)

# List the include paths
xmake_import_search_paths(ZLIB)

# Declaration of the library
xmake_create_static_library(PNG png ${HEADERS} ${SRCS})

# ---------- START

target_include_directories(png PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/FreeImage>
)

xmake_install_target(png)

install(FILES ${HEADERS}
    DESTINATION include/FreeImage/png
)

# ---------- FINISH

include("${CMAKE_SOURCE_DIR}/CompilerTypeFix.cmake")
fixCompilerType(PNG)

xmake_project_link(PNG ZLIB)
