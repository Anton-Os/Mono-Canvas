add_executable(VEruption src/Prime.cpp)

target_include_directories(VEruption PUBLIC ${Vulkan_INCLUDE_DIR})

target_link_libraries(VEruption 
    ${Vulkan_LIBRARY}
    glfw
)