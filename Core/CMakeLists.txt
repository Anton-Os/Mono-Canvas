add_executable(CalcGraph
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_Entity.cpp
    source/geometry/GL4_PolyFunc.cpp
    source/pipeline/GLSL_Idle.cpp
    main/Demo_CalcGraph.cpp
)

target_include_directories(CalcGraph
    PUBLIC include
)

target_link_libraries(CalcGraph
    GLEW::glew_s
    glfw
    glm
)

add_executable(IdxCube
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_Entity.cpp
    source/geometry/GL4_PolyFunc.cpp
    source/geometry/polyform/Polyform_Grid.cpp
    source/pipeline/GLSL_Idle.cpp
    main/Demo_IdxCube.cpp
)

target_include_directories(IdxCube
    PUBLIC include
)

target_link_libraries(IdxCube
    GLEW::glew_s
    glfw
    glm
)

add_executable(Rounding
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_Entity.cpp
    source/geometry/GL4_PolyAngles.cpp
    source/geometry/polyform/Polyform_Circle.cpp
    source/pipeline/GLSL_Idle.cpp
    main/Demo_Rounding.cpp
)

target_include_directories(Rounding
    PUBLIC include
)

target_link_libraries(Rounding
    GLEW::glew_s
    glfw
    glm
)

add_executable(Spectrum
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_Entity.cpp
    source/geometry/GL4_PolyFunc.cpp
    source/geometry/polyform/Polyform_Box.cpp
    source/geometry/polyform/Polyform_Rubiks.cpp
    source/pipeline/GLSL_Idle.cpp
    source/pipeline/GLSL_ColorMe.cpp
    main/Demo_Spectrum.cpp
)

target_include_directories(Spectrum
    PUBLIC include
)

target_link_libraries(Spectrum
    GLEW::glew_s
    glfw
    glm
)

add_executable(Galactica
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_Entity.cpp
    source/geometry/GL4_PolyFunc.cpp
    source/geometry/polyform/Polyform_Box.cpp
    source/geometry/polyform/Polyform_Rubiks.cpp
    source/pipeline/GLSL_Idle.cpp
    source/pipeline/GLSL_ColorMe.cpp
    main/Demo_Galactica.cpp
)

target_include_directories(Galactica
    PUBLIC include
)

target_link_libraries(Galactica
    GLEW::glew_s
    glfw
    glm
)

add_executable(Editor
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_Entity.cpp
    source/geometry/GL4_PolyFunc.cpp
    source/geometry/polyform/Polyform_Box.cpp
    source/geometry/polyform/Polyform_Rubiks.cpp
    source/pipeline/GLSL_Idle.cpp
    source/scene/Editor.cpp
    main/Demo_Editor.cpp
)

target_include_directories(Editor
    PUBLIC include
)

target_link_libraries(Editor
    GLEW::glew_s
    glfw
    glm
)

add_executable(Cloning
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_Entity.cpp
    source/geometry/GL4_Tree.cpp
    source/geometry/GL4_PolyFunc.cpp
    source/geometry/GL4_PolyClone.cpp
    source/geometry/polyform/Polyform_Box.cpp
    source/geometry/polyform/Polyform_Grid.cpp
    source/pipeline/GLSL_Idle.cpp
    source/scene/Cellular.cpp # For Testing
    main/Demo_Cloning.cpp
)

target_include_directories(Cloning
    PUBLIC include
)

target_link_libraries(Cloning
    GLEW::glew_s
    glfw
    glm 
)

add_executable(Cellular
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_Entity.cpp
    source/geometry/GL4_PolyFunc.cpp
    source/geometry/polyform/Polyform_Box.cpp
    source/geometry/polyform/Polyform_Grid.cpp
    source/pipeline/GLSL_Idle.cpp
    source/scene/Cellular.cpp # For Testing
    main/Demo_Cellular.cpp
)

target_include_directories(Cellular
    PUBLIC include
)

target_link_libraries(Cellular
    GLEW::glew_s
    glfw
    glm 
)

set(SRC_SHADER_LIST)
set(OUTPUT_SHADER_LIST)
foreach(current_shader "Idle.vert" "Idle.frag"
                       "ColorMe.vert" "ColorMe.frag" 
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
add_custom_target(Core_Shaders
    SOURCES ${SRC_SHADER_LIST}
    DEPENDS ${OUTPUT_SHADER_LIST}
)

add_dependencies(CalcGraph Core_Shaders)