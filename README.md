# PolyArt

### Supported generators:

- Visual Studio 14 2015 (or greater)
- MinGW Makefiles

### Build Instructions:

1. Build dependencies. Create a new CMake project with the source directory specified as PolyArt/Extlib, set the CACHE entry CMAKE_INSTALL_PREFIX to a path on your local file system
2. Navigate to the dependencies build directory and invoke cmake --build . 

3. Build the main project. Set CACHE entry CMAKE_INSTALL_PREFIX so that it matches the one you set in step #1. Set CACHE entry EXTLIB_BUILD_PATH to the build directory for your dependencies set in step #2.
4. Navigate to the main project build directory and invoke cmake --build .

### Directory Structure:

Core/source/geometry/ - for generating, analyzing, rendering geometric entities
Core/source/loaders/ - for retrieving and exporting application data
Core/source/pipeline/ - for operating on shader programs
Core/source/scene/ - for interactivity between user and scene elements