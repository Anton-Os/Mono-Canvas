add_executable(Abstraction
    src/LoadTextures.cpp
    src/LoadShaders.cpp
    src/Model3D.cpp
    revision/AssimpModel.cpp
    src/NoBlocks.cpp
    revision/CrossContext.cpp
    revision/Prime.cpp
)

target_include_directories(Abstraction
    PUBLIC include
)

target_link_libraries(Abstraction
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
                       "NoBlocks.vert" "NoBlocks.frag"
                       "LitBlocks.vert" "LitBlocks.frag"
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
add_custom_target(AbsShaders
    SOURCES ${SRC_SHADER_LIST}
    DEPENDS ${OUTPUT_SHADER_LIST}
)

add_dependencies(AssimpModels AbsShaders)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/GDrive.cmake.in" 
               "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GDrive.cmake"
                @ONLY
)
add_custom_target(GDrive ALL 
    ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GDrive.cmake"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GDrive.cmake"
)