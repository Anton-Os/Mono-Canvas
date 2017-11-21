add_executable(Blank
    loaders/LoadShaders.cpp
    geometry/GL4_DataSet.cpp
    pipeline/GLSL_Idle.cpp
    main/Blank.cpp
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
    loaders/LoadShaders.cpp
    loaders/LoadData.cpp
    pipeline/GLSL_Idle.cpp
    geometry/GL4_Sphere.cpp
    geometry/GL4_BumpGrid.cpp
    main/LoopTimed.cpp
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
    loaders/LoadShaders.cpp
    loaders/LoadData.cpp
    pipeline/GLSL_Idle.cpp
    pipeline/GLSL_HeightRange.cpp
    geometry/GL4_BumpGrid.cpp
    main/Hills.cpp
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
    loaders/LoadShaders.cpp
    pipeline/GLSL_Idle.cpp
    pipeline/GLSL_HeightRange.cpp
    geometry/GL4_Sphere.cpp
    geometry/GL4_BumpGrid.cpp
    geometry/GL4_DataSet.cpp
    scene/PlaneCollision.cpp
    main/MidPoints.cpp
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
    loaders/LoadShaders.cpp
    pipeline/GLSL_Idle.cpp
    pipeline/GLSL_HeightRange.cpp
    geometry/GL4_Sphere.cpp
    geometry/GL4_BumpGrid.cpp
    geometry/GL4_DataSet.cpp
    scene/PlaneCollision.cpp
    main/CollisionTest.cpp
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
    loaders/LoadShaders.cpp
    pipeline/GLSL_Idle.cpp
    pipeline/GLSL_Flatscape.cpp
    pipeline/GLSL_Fractals.cpp
    geometry/GL4_DataSet.cpp
    scene/PlaneCollision.cpp
    main/MandlebrotSet.cpp
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
    loaders/LoadShaders.cpp
    geometry/GL4_DataSet.cpp
    geometry/GL4_Grid.cpp
    geometry/GL4_BumpGrid
    pipeline/GLSL_Idle.cpp
    pipeline/GLSL_StateStream.cpp
    scene/CellSim.cpp
    main/ConwaysGOL.cpp
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
    loaders/LoadShaders.cpp
    geometry/GL4_DataSet.cpp
    geometry/GL4_Grid.cpp
    geometry/GL4_HexGrid.cpp
    pipeline/GLSL_Idle.cpp
    pipeline/GLSL_StateStream.cpp
    scene/CellSim.cpp
    main/Hexes.cpp
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
    loaders/LoadShaders.cpp
    pipeline/GLSL_Idle.cpp
    pipeline/GLSL_HeightRange.cpp
    pipeline/GLSL_Waves.cpp
    geometry/GL4_Sphere.cpp
    geometry/GL4_BumpGrid.cpp
    geometry/GL4_DataSet.cpp
    scene/PlaneCollision.cpp
    main/Ripples.cpp
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
    loaders/LoadShaders.cpp
    pipeline/GLSL_Idle.cpp
    pipeline/GLSL_HeightRange.cpp
    pipeline/GLSL_Waves.cpp
    geometry/GL4_Sphere.cpp
    geometry/GL4_BumpGrid.cpp
    geometry/GL4_DataSet.cpp
    scene/PlaneCollision.cpp
    main/StackedRipples.cpp
)

target_include_directories(StackedRipples
    PUBLIC include
)

target_link_libraries(StackedRipples
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

add_dependencies(LoopTimed Core_Shaders)
add_dependencies(Hills Core_Shaders)