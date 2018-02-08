add_executable(Idle
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/graphics/factory/GL4_Vertex_Factory.cpp
    source/graphics/entity/GL4_Mesh.cpp
    source/geometry/pseudo/Hedgy.cpp
    source/scene/ErrorCode.cpp
    main/Demo_Idle.cpp
)

target_include_directories(Idle
    PUBLIC
    include
)

target_link_libraries(Idle
    GLEW::glew_s
    glfw
    glm
)

add_executable(Comeback
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/graphics/factory/GL4_Vertex_Factory.cpp
    source/graphics/entity/GL4_Mesh.cpp
    source/geometry/polybase/GL4_PolyFunc.cpp
    source/geometry/polyform/GL4_PolyGrid.cpp
    source/scene/ErrorCode.cpp
    source/scene/KeyManager.cpp
    main/Demo_Comeback.cpp
)

target_include_directories(Comeback
    PUBLIC
    include
)

target_link_libraries(Comeback
    GLEW::glew_s
    glfw
    glm
)

add_executable(ShaderWorks
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/graphics/factory/GL4_Vertex_Factory.cpp
    source/graphics/entity/GL4_Mesh.cpp
    source/geometry/polybase/GL4_PolyFunc.cpp
    source/geometry/polyform/GL4_PolyGrid.cpp
    source/graphics/GL4_Program.cpp
    source/graphics/GL4_Uniform.cpp
    source/graphics/factory/GL4_Uniform_Factory.cpp
    source/graphics/factory/GL4_Shader_Factory.cpp
    source/scene/ErrorCode.cpp
    source/scene/KeyManager.cpp
    main/Demo_ShaderWorks.cpp
)

target_include_directories(ShaderWorks
    PUBLIC
    include
)

target_link_libraries(ShaderWorks
    GLEW::glew_s
    glfw
    glm
)

set(RES_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/res")
configure_file("${CMAKE_CURRENT_LIST_DIR}/cmake/GDrive.cmake" "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/GDrive.cmake" @ONLY)
add_custom_target(Core_V3_GDrive ALL 
    ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/GDrive.cmake"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/GDrive.cmake"
)

set(SRC_SHADER_LIST)
set(OUTPUT_SHADER_LIST)
foreach(current_shader "Idle.vert" "Idle.frag"
            "Tones.vert" "Tones.frag"
)
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/shaders/${current_shader}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/shaders/${current_shader}"
        COMMAND ${GLSLC_EXE} ARGS "${CMAKE_CURRENT_LIST_DIR}/shaders/${current_shader}" -S -g --target-env=opengl -x glsl
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_LIST_DIR}/shaders/${current_shader}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/shaders/${current_shader}"    
    )
    list(APPEND OUTPUT_SHADER_LIST "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/shaders/${current_shader}")
    list(APPEND SRC_SHADER_LIST "${CMAKE_CURRENT_SOURCE_DIR}/shaders/${current_shader}")
endforeach(current_shader)
add_custom_target(Core_V3_Shaders
    SOURCES ${SRC_SHADER_LIST}
    DEPENDS ${OUTPUT_SHADER_LIST}
)

add_dependencies(Idle Core_V3_Shaders)
