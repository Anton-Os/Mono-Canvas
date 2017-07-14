cmake_minimum_required(VERSION 2.8)
project(Img2KTX)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Download prebuilt binaries
    message(STATUS "Installing prebuilt binaries for Windows64 bit")
    install(FILES
        "${CMAKE_SOURCE_DIR}/win64-prebuilt/img2ktx.exe"
        "${CMAKE_SOURCE_DIR}/win64-prebuilt/ispc_texcomp.dll"
        DESTINATION bin
    )
endif()

# add_executable(img2ktx img2ktx.cpp)
# target_link_libraries(img2ktx "${CMAKE_SOURCE_DIR}/")