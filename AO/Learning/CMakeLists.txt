
# add_executable(Hello "HelloGL.cpp")
add_executable(Prime1 Prime/Prime-A.cpp)
add_executable(Prime2 Prime/Prime-C.cpp)
# add_executable(FreeImageTest FreeImageTest.cpp)
# add_executable(Prime3 LoadShaders/LoadShaders-C.cpp Prime/Prime-D.cpp)
add_executable(Prime3 Textures/TexturesGL-C.cpp LoadShaders/LoadShaders-E.cpp Prime/Prime-E.cpp)
# add_executable(Dummy Prime/Prime-x.cpp)
# add_executable(TexturesGL1 Textures/TexturesGL-B.cpp)
# add_executable(TexturesGL1 Textures/TexturesGL-A.cpp)

target_link_libraries(Prime1
    GLEW::glew_s
    glfw
)

target_link_libraries(Prime2
    GLEW::glew_s
    glfw
)

target_include_directories(Prime3
    PUBLIC include
)

target_link_libraries(Prime3
    GLEW::glew_s
    glfw
    gli
    glm
)

# target_link_libraries(TexturesGL1
#    GLEW::glew_s
#    gli
#    glm
# )

#[[ target_link_libraries(TexturesGL1
    GLEW::glew_s
#    freeimage::jpeg
    freeimage::freeimage
) #]]

add_custom_target(MonoShaders
    COMMENT "Edit shader files"
    SOURCES "shaders/Mono1.vert" "shaders/Mono1.frag" 
)

foreach(current_shader "Mono1.vert" "Mono1.frag")
    add_custom_command(TARGET Prime3
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_LIST_DIR}/Shaders/${current_shader}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${current_shader}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Shaders/${current_shader}"
    )
endforeach(current_shader)

set(TEXTURES_JPG)
set(TEXTURES_KTX)
set(TEXTURES_KTX_DIR "data/ktx")
list(APPEND TEXTURES_JPG "Concrete-1.jpg" "Concrete-2.jpg" "Concrete-3.jpg" "Ice-1.jpg" "Metal-1.jpg")
list(APPEND TEXTURES_KTX "Metal-1.ktx" "Container-1.KTX")

foreach(current_texture ${TEXTURES_KTX})
    add_custom_command(TARGET Prime3
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            # "${CMAKE_CURRENT_LIST_DIR}/Textures/JPG/${current_texture}"
            "${CMAKE_CURRENT_LIST_DIR}/${TEXTURES_KTX_DIR}/${current_texture}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${TEXTURES_KTX_DIR}/${current_texture}"
            # Fix previous line to detect wether name contains parent directory
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/${TEXTURES_KTX_DIR}/${current_texture}"    
    )
endforeach(current_texture)
