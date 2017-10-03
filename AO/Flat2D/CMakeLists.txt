add_executable(Demo2D
    loaders/LoadShaders.cpp
    loaders/LoadData.cpp
    pipeline/Locked.cpp
    feed/GL4-BufferFeeder.cpp
    Demo2D.cpp
)

target_include_directories(Demo2D
    PUBLIC 
    include
    ${BOOST_INCLUDEDIR}
)

target_link_libraries(Demo2D
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
foreach(current_shader "Locked.vert" "Locked.frag"
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
add_custom_target(Flat2D_Shaders
    SOURCES ${SRC_SHADER_LIST}
    DEPENDS ${OUTPUT_SHADER_LIST}
)

add_dependencies(Demo2D Flat2D_Shaders)