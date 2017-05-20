cmake_minimum_required(VERSION 3.6)
project(PicoPixelClient)

add_library(PicoPixelClient SHARED "SDK/PicoPixelClient.cpp")
add_library(PicoPixelClient_static STATIC "SDK/PicoPixelClient.cpp")

target_include_directories(PicoPixelClient
    PUBLIC
    $<BUILD_INTERFACE:${PICOPIXELCLIENT_PROJECT_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)

target_include_directories(PicoPixelClient_static
    PUBLIC
    $<BUILD_INTERFACE:${PICOPIXELCLIENT_PROJECT_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)

set(picopixelclient_targets)
list(APPEND picopixelclient_targets PicoPixelClient PicoPixelClient_static)

install(TARGETS ${picopixelclient_targets}
    EXPORT picopixelclientTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(EXPORT picopixelclientTargets
    FILE PicoPixelClientTargets.cmake
    DESTINATION lib/cmake/PicoPixelClient
)

export(EXPORT picopixelclientTargets
    FILE PicoPixelClientTargets.cmake
)

install(FILES "${PICOPIXELCLIENT_PROJECT_DIR}/PicoPixelClientConfig.cmake"
    DESTINATION lib/cmake/PicoPixelClient
)

install(FILES "PicoPixelClientTest/opengl-gears.exe"
    DESTINATION bin
)

install(FILES "${PICOPIXELCLIENT_PROJECT_DIR}/PicoPixelClent.h" 
              "${PICOPIXELCLIENT_PROJECT_DIR}/PicoPixelClientProtocol.h"
    DESTINATION include
)