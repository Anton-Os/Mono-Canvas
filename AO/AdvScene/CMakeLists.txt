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
    gli
    glm
    assimp
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
    gli
    glm
    assimp
)

add_executable(MidPoints
    loaders/LoadShaders.cpp
    loaders/LoadData.cpp
    pipeline/GLSL_Idle.cpp
    pipeline/GLSL_HeightRange.cpp
    geometry/GL4_Sphere.cpp
    geometry/GL4_BumpGrid.cpp
    geometry/GL4_DataSet.cpp
    scene/Scene_PlaneCollision.cpp
    main/MidPoints.cpp
)

target_include_directories(MidPoints
    PUBLIC include
)

target_link_libraries(MidPoints
    GLEW::glew_s
    glfw
    gli
    glm
    assimp
)

add_executable(CollisionTest
    loaders/LoadShaders.cpp
    loaders/LoadData.cpp
    pipeline/GLSL_Idle.cpp
    pipeline/GLSL_HeightRange.cpp
    geometry/GL4_Sphere.cpp
    geometry/GL4_BumpGrid.cpp
    geometry/GL4_DataSet.cpp
    scene/Scene_PlaneCollision.cpp
    main/CollisionTest.cpp
)

target_include_directories(CollisionTest
    PUBLIC include
    ${BOOST_INCLUDEDIR}
)

target_link_libraries(CollisionTest
    GLEW::glew_s
    glfw
    gli
    glm
    assimp
    ${BOOST_LIBS} 
)

# WORK WITH SHADER FILES

set(SRC_SHADER_LIST)
set(OUTPUT_SHADER_LIST)
foreach(current_shader "Idle.vert" "Idle.frag"
                       "HeightRange.vert" "HeightRange.frag"
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
add_custom_target(AdvScene_Shaders
    SOURCES ${SRC_SHADER_LIST}
    DEPENDS ${OUTPUT_SHADER_LIST}
)

add_dependencies(LoopTimed AdvScene_Shaders)
add_dependencies(Hills AdvScene_Shaders)