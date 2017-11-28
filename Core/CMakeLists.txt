
add_executable(Blank
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_DataSet.cpp
    source/pipeline/GLSL_Idle.cpp
    demos/Blank.cpp
)

target_include_directories(Blank
    PUBLIC include
)

target_link_libraries(Blank
    GLEW::glew_s
    glfw
    glm
)


add_executable(LoopTimed
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/loaders/LoadData.cpp
    source/pipeline/GLSL_Idle.cpp
    source/geometry/GL4_Sphere.cpp
    demos/LoopTimed.cpp
)

target_include_directories(LoopTimed
PUBLIC include
)

target_link_libraries(LoopTimed
    GLEW::glew_s
    glfw
    glm
)

add_executable(Hills
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/loaders/LoadData.cpp
    source/pipeline/GLSL_Idle.cpp
    source/pipeline/GLSL_HeightRange.cpp
    source/geometry/GL4_BumpGrid.cpp
    demos/Hills.cpp
)

target_include_directories(Hills
    PUBLIC include
)

target_link_libraries(Hills
    GLEW::glew_s
    glfw
    glm
)

add_executable(MidPoints
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/pipeline/GLSL_Idle.cpp
    source/pipeline/GLSL_HeightRange.cpp
    source/geometry/GL4_Sphere.cpp
    source/geometry/GL4_BumpGrid.cpp
    source/geometry/GL4_DataSet.cpp
    source/scene/PlaneCollision.cpp
    demos/MidPoints.cpp
)

target_include_directories(MidPoints
    PUBLIC include
)

target_link_libraries(MidPoints
    GLEW::glew_s
    glfw
    glm
)

add_executable(CollisionTest
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/pipeline/GLSL_Idle.cpp
    source/pipeline/GLSL_HeightRange.cpp
    source/geometry/GL4_Sphere.cpp
    source/geometry/GL4_BumpGrid.cpp
    source/geometry/GL4_DataSet.cpp
    source/scene/PlaneCollision.cpp
    demos/CollisionTest.cpp
)

target_include_directories(CollisionTest
    PUBLIC include
)

target_link_libraries(CollisionTest
    GLEW::glew_s
    glfw
    glm
)

add_executable(MandlebrotSet
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/pipeline/GLSL_Idle.cpp
    source/pipeline/GLSL_Flatscape.cpp
    source/pipeline/GLSL_Fractals.cpp
    source/geometry/GL4_DataSet.cpp
    demos/MandlebrotSet.cpp
)

target_include_directories(MandlebrotSet
    PUBLIC include
)

target_link_libraries(MandlebrotSet
    GLEW::glew_s
    glfw
    gli
    glm
    assimp
)

add_executable(ConwaysGOL
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_DataSet.cpp
    source/geometry/GL4_Grid.cpp
    source/geometry/GL4_BumpGrid
    source/pipeline/GLSL_Idle.cpp
    source/pipeline/GLSL_StateStream.cpp
    source/scene/CellSim.cpp
    demos/ConwaysGOL.cpp
)

target_include_directories(ConwaysGOL
    PUBLIC include
)

target_link_libraries(ConwaysGOL
    GLEW::glew_s
    glfw
    glm
)

add_executable(Hexes
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_DataSet.cpp
    source/geometry/GL4_Grid.cpp
    source/geometry/GL4_HexGrid.cpp
    source/pipeline/GLSL_Idle.cpp
    source/pipeline/GLSL_StateStream.cpp
    demos/Hexes.cpp
)

target_include_directories(Hexes
    PUBLIC include
)

target_link_libraries(Hexes
    GLEW::glew_s
    glfw
    glm
)

add_executable(Ripples
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/pipeline/GLSL_Idle.cpp
    source/pipeline/GLSL_HeightRange.cpp
    source/pipeline/GLSL_Waves.cpp
    source/geometry/GL4_Sphere.cpp
    source/geometry/GL4_BumpGrid.cpp
    source/geometry/GL4_DataSet.cpp
    demos/Ripples.cpp
)

target_include_directories(Ripples
    PUBLIC include
)

target_link_libraries(Ripples
    GLEW::glew_s
    glfw
    glm
)

add_executable(StackedRipples
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/pipeline/GLSL_Idle.cpp
    source/pipeline/GLSL_HeightRange.cpp
    source/pipeline/GLSL_Waves.cpp
    source/geometry/GL4_Sphere.cpp
    source/geometry/GL4_BumpGrid.cpp
    source/geometry/GL4_DataSet.cpp
    demos/StackedRipples.cpp
)

target_include_directories(StackedRipples
    PUBLIC include
)

target_link_libraries(StackedRipples
    GLEW::glew_s
    glfw
    glm
)

add_executable(RenderMath
    source/loaders/FileIO.cpp
    source/loaders/LoadShaders.cpp
    source/geometry/GL4_DataSet.cpp
    source/geometry/GL4_PolyFunc.cpp
    source/pipeline/GLSL_Idle.cpp
    demos/RenderMath.cpp
)

target_include_directories(RenderMath
    PUBLIC include
)

target_link_libraries(RenderMath
    GLEW::glew_s
    glfw
    glm
)


set(SRC_SHADER_LIST)
set(OUTPUT_SHADER_LIST)
foreach(current_shader "Idle.vert" "Idle.frag"
                   "HeightRange.vert" "HeightRange.frag"
                   "Flatscape.vert" "Flatscape.frag"
                   "Fractals.vert" "Fractals.frag"
                   "StateStream.vert" "StateStream.frag"
                   "Waves.vert" "Waves.frag"
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

add_dependencies(Blank Core_Shaders)