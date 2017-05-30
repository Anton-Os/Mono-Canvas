add_executable(MonoCanvas-A src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-Texturize.cpp)
add_executable(MonoCanvas-B src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-Transform.cpp)


target_include_directories(MonoCanvas-A
    PUBLIC include
)

target_link_libraries(MonoCanvas-A
    GLEW::glew_s
    glfw
    gli
    glm
)

target_include_directories(MonoCanvas-B
    PUBLIC include
)

target_link_libraries(MonoCanvas-B
    GLEW::glew_s
    glfw
    gli
    glm
)

# WORK WITH SHADER FILES

add_custom_target(MonoShaders
    COMMENT "Edit shader files"
    SOURCES "shaders/AO-1.vert" "shaders/AO-1.frag" 
            "shaders/AO-2.vert" "shaders/AO-2.frag"
            "shaders/AO-3.vert" "shaders/AO-3.frag" 
            "shaders/AO-4.vert" 
)

set(OUTPUT_SHADER_LIST)
foreach(current_shader "AO-1.vert" "AO-1.frag" 
                       "AO-2.vert" "AO-2.frag"
                       "AO-3.vert" "AO-3.frag"
                       "AO-4.vert"
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
add_dependencies(MonoCanvas-B Shaders)


# WORK WITH TEXTURE/IMAGE FILES

set(TEXTURES_JPG)
set(TEXTURES_KTX)
set(TEXTURES_KTX_DIR "data/ktx")
list(APPEND TEXTURES_JPG "Concrete-1.jpg" "Concrete-2.jpg" "Concrete-3.jpg" "Ice-1.jpg" "Metal-1.jpg")
list(APPEND TEXTURES_KTX "Metal-1.ktx" "Container-1.KTX" "Texture8_PNG_BC7_1.KTX")

foreach(current_texture ${TEXTURES_KTX})
    add_custom_command(TARGET MonoCanvas-B
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_LIST_DIR}/${TEXTURES_KTX_DIR}/${current_texture}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${TEXTURES_KTX_DIR}/${current_texture}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/${TEXTURES_KTX_DIR}/${current_texture}"    
    )
endforeach(current_texture)
