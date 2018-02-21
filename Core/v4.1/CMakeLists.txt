add_executable(Tiles
    source/loaders/FileIO.cpp
    source/graphics/GL4_LoadShaders.cpp
    source/graphics/factory/GL4_Vertex_Factory.cpp
    source/scene/ErrorCode.cpp
    source/scene/KeyManager.cpp
    main/Demo_Tiles.cpp
)

target_include_directories(Tiles
    PUBLIC
    include
)

target_link_libraries(Tiles
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


if(Shaderc_MODULE)
    set(SRC_SHADER_LIST)
    set(OUTPUT_SHADER_LIST)
    foreach(current_shader "Idle.vert" "Idle.frag"
                "Tones.vert" "Tones.frag"
                "Flatland.vert" "Flatland.frag"
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
    add_custom_target(Core_V4_Shaders
        SOURCES ${SRC_SHADER_LIST}
        DEPENDS ${OUTPUT_SHADER_LIST}
    )

    add_dependencies(Tiles Core_V4_Shaders)
else()
    foreach(current_shader "Idle.vert" "Idle.frag"
        "Tones.vert" "Tones.frag"
        "Flatland.vert" "Flatland.frag"
    )
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/shaders/${current_shader}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/shaders/${current_shader}")
    endforeach(current_shader)
endif()