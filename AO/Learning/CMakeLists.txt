add_executable(MonoCanvas src/LoadTextures.cpp src/LoadShaders.cpp src/Prime.cpp)

target_include_directories(MonoCanvas
    PUBLIC include
)

target_link_libraries(MonoCanvas
    GLEW::glew_s
    glfw
    gli
    glm
)

# WORK WITH SHADER FILES

add_custom_target(MonoShaders
    COMMENT "Edit shader files"
    SOURCES "shaders/Mono1.vert" "shaders/Mono1.frag" 
)

foreach(current_shader "Mono1.vert" "Mono1.frag")
    add_custom_command(TARGET MonoCanvas
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_LIST_DIR}/Shaders/${current_shader}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${current_shader}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Shaders/${current_shader}"
    )
endforeach(current_shader)

# WORK WITH TEXTURE/IMAGE FILES

set(TEXTURES_JPG)
set(TEXTURES_KTX)
set(TEXTURES_KTX_DIR "data/ktx")
list(APPEND TEXTURES_JPG "Concrete-1.jpg" "Concrete-2.jpg" "Concrete-3.jpg" "Ice-1.jpg" "Metal-1.jpg")
list(APPEND TEXTURES_KTX "Metal-1.ktx" "Container-1.KTX")

foreach(current_texture ${TEXTURES_KTX})
    add_custom_command(TARGET MonoCanvas
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_LIST_DIR}/${TEXTURES_KTX_DIR}/${current_texture}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${TEXTURES_KTX_DIR}/${current_texture}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/${TEXTURES_KTX_DIR}/${current_texture}"    
    )
endforeach(current_texture)
