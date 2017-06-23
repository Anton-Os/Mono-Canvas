add_executable(Scene360 src/LoadTextures.cpp src/LoadShaders.cpp src/Prime.cpp)

target_include_directories(Scene360
    PUBLIC include
)

target_link_libraries(Scene360
    GLEW::glew_s
    glfw
    gli
    glm
)

# WORK WITH SHADER FILES

add_custom_target(MonoShaders
    COMMENT "Edit shader files"
    SOURCES "shaders/Viewer3D.vert" "shaders/Viewer3D.frag"
)

set(OUTPUT_SHADER_LIST)
foreach(current_shader "Viewer3D.vert" "Viewer3D.frag"
)
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${current_shader}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/shaders/${current_shader}"
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_LIST_DIR}/shaders/${current_shader}"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${current_shader}"
    )
    list(APPEND OUTPUT_SHADER_LIST "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${current_shader}")
    #add_dependencies(MonoCanvas-B "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${current_shader}")
endforeach(current_shader)
add_custom_target(Shaders
    DEPENDS ${OUTPUT_SHADER_LIST}
)
add_dependencies(Scene360 Shaders)

# WORK WITH TEXTURE/IMAGE FILES

set(TEXTURES_KTX)
set(TEXTURES_KTX_DIR "data/ktx")
list(APPEND TEXTURES_KTX "Illusions.KTX" 
                         "Wood.KTX"
                         "SpottedSteel.KTX"
                         "CreasedWhitePaper.KTX"
                         "Concrete.KTX"
)

foreach(current_texture ${TEXTURES_KTX})
    add_custom_command(TARGET Scene360
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_LIST_DIR}/${TEXTURES_KTX_DIR}/${current_texture}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${TEXTURES_KTX_DIR}/${current_texture}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/${TEXTURES_KTX_DIR}/${current_texture}"    
    )
endforeach(current_texture)
