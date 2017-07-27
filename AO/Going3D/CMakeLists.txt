add_executable(AssimpModels
    src/LoadTextures.cpp
    src/LoadShaders.cpp
    src/Model3D.cpp
    src/NoBlocks.cpp
    src/Prime.cpp
)

target_include_directories(AssimpModels
    PUBLIC include
)

target_link_libraries(AssimpModels
    GLEW::glew_s
    glfw
    gli
    glm
    assimp
)

# WORK WITH SHADER FILES

set(SRC_SHADER_LIST)
set(OUTPUT_SHADER_LIST)
foreach(current_shader "Viewer3D.vert" "Viewer3D.frag"
                       "LitEnv.vert" "LitEnv.frag"
                       "ModelStatic.vert" "ModelStatic.frag"
                       "NoBlocks.vert" "NoBlocks.frag"
)
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${current_shader}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/shaders/${current_shader}"
        COMMAND ${GLSLC_EXE} ARGS "${CMAKE_CURRENT_LIST_DIR}/shaders/${current_shader}" -S -g --target-env=opengl -x glsl
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_LIST_DIR}/shaders/${current_shader}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/shaders/${current_shader}"    
    )
    list(APPEND OUTPUT_SHADER_LIST "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${current_shader}")
    list(APPEND SRC_SHADER_LIST "${CMAKE_CURRENT_SOURCE_DIR}/shaders/${current_shader}")
endforeach(current_shader)
add_custom_target(MonoShaders
    SOURCES ${SRC_SHADER_LIST}
    DEPENDS ${OUTPUT_SHADER_LIST}
)

add_dependencies(AssimpModels MonoShaders)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/GDrive.cmake.in" "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GDrive.cmake")
add_custom_target(GDrive ALL 
    ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GDrive.cmake"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GDrive.cmake"
)