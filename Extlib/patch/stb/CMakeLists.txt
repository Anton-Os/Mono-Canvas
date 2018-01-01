cmake_minimum_required(VERSION 3.6)
project(stb)

file(GLOB stb_headers *.h)

install(FILES
    ${stb_headers}
    DESTINATION "${CMAKE_INSTALL_PREFIX}/include/stb/stb"
)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_INSTALL_PREFIX}/include/stb)

install(TARGETS stb EXPORT stb_target DESTINATION lib)
install(EXPORT stb_target DESTINATION lib/cmake/stb FILE stbTarget.cmake)
configure_file("${CMAKE_SOURCE_DIR}/stbConfig.cmake.in" "${CMAKE_SOURCE_DIR}/stbConfig.cmake")
install(FILES "stbConfig.cmake" DESTINATION lib/cmake/stb)