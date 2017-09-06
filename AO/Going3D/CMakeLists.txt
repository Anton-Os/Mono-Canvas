add_executable(AssimpModels
    comp/LoadTextures.cpp
    comp/LoadShaders.cpp
    comp/Model3D.cpp
    # comp/ShaderCtrl.cpp
    pipeline/NoBlocks.cpp
    main/AssimpModels.cpp
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

add_executable(Textureless
    comp/LoadTextures.cpp
    comp/LoadShaders.cpp
    comp/Model3D.cpp
    # comp/ShaderCtrl.cpp
    pipeline/LitEnv.cpp
    main/Textureless.cpp
)

target_include_directories(Textureless
    PUBLIC include
)

target_link_libraries(Textureless
    GLEW::glew_s
    glfw
    gli
    glm
    assimp
)

add_executable(FluidCamera
    comp/LoadTextures.cpp
    comp/LoadShaders.cpp
    comp/Model3D.cpp
    pipeline/LitEnv.cpp
    main/FluidCamera.cpp
)

target_include_directories(FluidCamera
    PUBLIC include
)

target_link_libraries(FluidCamera
    GLEW::glew_s
    glfw
    gli
    glm
    assimp
)

# WORK WITH SHADER FILES

set(SRC_SHADER_LIST)
set(OUTPUT_SHADER_LIST)
foreach(current_shader "LitEnv.vert" "LitEnv.frag"
                       "NoBlocks.vert" "NoBlocks.frag"
                       "V-Instanced.vert" "V-Instanced.frag"
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
add_dependencies(Textureless MonoShaders)