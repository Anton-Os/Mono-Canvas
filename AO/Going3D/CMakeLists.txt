add_executable(TextureTrial src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-A.cpp)
add_executable(SpinningShape src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-B.cpp)
add_executable(ProjetionDraft src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-C.cpp)
add_executable(MatrixViews src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-D.cpp)
add_executable(PerspectiveCopy src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-E.cpp)
add_executable(ManyCubes src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-F.cpp)
add_executable(LookAhead src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-G.cpp)
add_executable(Scene360 src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-I.cpp)

target_include_directories(TextureTrial
    PUBLIC include
)

target_link_libraries(TextureTrial
    GLEW::glew_s
    glfw
    gli
    glm
)

target_include_directories(SpinningShape
    PUBLIC include
)

target_link_libraries(SpinningShape
    GLEW::glew_s
    glfw
    gli
    glm
)

target_include_directories(ProjetionDraft
    PUBLIC include
)

target_link_libraries(ProjetionDraft
    GLEW::glew_s
    glfw
    gli
    glm
)

target_include_directories(MatrixViews
    PUBLIC include
)

target_link_libraries(MatrixViews
    GLEW::glew_s
    glfw
    gli
    glm
)

target_include_directories(PerspectiveCopy
    PUBLIC include
)

target_link_libraries(PerspectiveCopy
    GLEW::glew_s
    glfw
    gli
    glm
)

target_include_directories(ManyCubes
    PUBLIC include
)

target_link_libraries(ManyCubes
    GLEW::glew_s
    glfw
    gli
    glm
)

target_include_directories(LookAhead
    PUBLIC include
)

target_link_libraries(LookAhead
    GLEW::glew_s
    glfw
    gli
    glm
)

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

#[[
add_custom_target(MonoShaders
    COMMENT "Edit shader files"
    SOURCES "shaders/AO-1.vert" "shaders/AO-1.frag" 
            "shaders/AO-2.vert" "shaders/AO-2.frag"
            "shaders/AO-3.vert" "shaders/AO-3.frag" 
            "shaders/AO-4.vert" "shaders/AO-4.frag" 
            "shaders/AO-5.vert" "shaders/AO-5.frag"
            "shaders/AO-6.vert" "shaders/AO-6.frag"
            "shaders/AO-7.vert" "shaders/AO-7.frag"
            "shaders/AO-8.vert" "shaders/AO-8.frag"
            "shaders/Viewer3D.vert" "shaders/Viewer3D.frag"
)
#]]

set(OUTPUT_SHADER_LIST)
foreach(current_shader "AO-1.vert" "AO-1.frag" 
                       "AO-2.vert" "AO-2.frag"
                       "AO-3.vert" "AO-3.frag"
                       "AO-4.vert" "AO-4.frag"
                       "AO-5.vert" "AO-5.frag"
                       "AO-6.vert" "AO-6.frag"
                       "AO-7.vert" "AO-7.frag"
                       "AO-8.vert" "AO-8.frag"
                       "Viewer3D.vert" "Viewer3D.frag"
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

add_dependencies(TextureTrial Shaders)
add_dependencies(SpinningShape Shaders)
add_dependencies(ProjetionDraft Shaders)
add_dependencies(MatrixViews Shaders)
add_dependencies(PerspectiveCopy Shaders)
add_dependencies(ManyCubes Shaders)
add_dependencies(LookAhead Shaders)
add_dependencies(Scene360 Shaders)

# WORK WITH TEXTURE/IMAGE FILES

set(TEXTURES_KTX)
set(TEXTURES_KTX_DIR "data/ktx")
list(APPEND TEXTURES_KTX "Texture8_PNG_BC7_1.KTX" 
                         "800px-Birnam_wood_macbeth_PNG_BC7_1.KTX"
                         "spotted-steel_PNG_BC7_3.KTX"
                         "wildtextures-creased-white-paper-texture_PNG_BC7_1.KTX"
                         "Concrete.ktx"
                         "SpottedSteel.KTX"
                         "CreasedWhitePaper.KTX"
                         "Wood.KTX"
                         "Illusions.KTX"
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
