# PolyArt

### Supported generators:

- Visual Studio 15 2017
- Visual Studio 14 2015
- MinGW Makefiles

### Build Instructions:

1. First create a cmake project with with the source directory pointing to Anton-Os/Mono-Canvas/Extlib and a build directory, ${EXTLIB_DIR}
2. Set CACHE variable CMAKE_INSTALL_PREFIX to an install directory, lets call it ${INSTALL_DIR}
3. Proceed to build the first project

4. Create a second cmake project with the source directory pointing to the root source directory Anton-Os/Mono-Canvas
5. Set CACHE variable CMAKE_INSTALL_PREFIX for this project to the ${INSTALL_DIR} set earlier
6. Set CACHE variable EXTLIB_BUILD_PATH for this project to the ${EXTLIB_DIR} set earlier
7. Proceed to build the second project
