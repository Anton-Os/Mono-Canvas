add_executable(CalcGraph
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_DataSet.cpp
    source/geometry/GL4_PolyFunc.cpp
    source/pipeline/GLSL_Idle.cpp
    main/CalcGraph.cpp
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
    source/geometry/GL4_DataSet.cpp
    source/geometry/GL4_PolyFunc.cpp
    source/geometry/poly/CartesianGrid.cpp
    source/pipeline/GLSL_Idle.cpp
    main/IdxCube.cpp
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
    source/geometry/GL4_DataSet.cpp
    source/geometry/GL4_PolyAngles.cpp
    source/geometry/poly/Circle.cpp
    source/pipeline/GLSL_Idle.cpp
    main/Rounding.cpp
)

target_include_directories(Rounding
    PUBLIC include
)

target_link_libraries(Rounding
    GLEW::glew_s
    glfw
    glm
)

set(SRC_SHADER_LIST)
set(OUTPUT_SHADER_LIST)
foreach(current_shader "Idle.vert" "Idle.frag")
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