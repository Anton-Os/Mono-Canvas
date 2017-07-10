add_executable(LookAhead src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-G.cpp)
add_executable(Scene360 src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-I.cpp)
add_executable(GoodCamera src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-J.cpp)
add_executable(PlatformTexture src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-K.cpp)
add_executable(Redesign src/LoadTextures.cpp src/LoadShaders.cpp src/Prime-L.cpp)

add_executable(LightFix src/LoadTextures.cpp src/LoadShaders.cpp src/Mesh.cpp src/Prime-M.cpp)
add_executable(AssimpModels
    src/Prime-N.cpp 
    src/LoadTextures.cpp
    src/LoadShaders.cpp
    src/Mesh.cpp
    src/Model3D.cpp
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

target_include_directories(GoodCamera
    PUBLIC include
)

target_link_libraries(GoodCamera
    GLEW::glew_s
    glfw
    gli
    glm
)

target_include_directories(PlatformTexture
    PUBLIC include
)

target_link_libraries(PlatformTexture
    GLEW::glew_s
    glfw
    gli
    glm
)

target_include_directories(Redesign
    PUBLIC include
)

target_link_libraries(Redesign
    GLEW::glew_s
    glfw
    gli
    glm
)

target_include_directories(LightFix
    PUBLIC include
)

target_link_libraries(LightFix
    GLEW::glew_s
    glfw
    gli
    glm
)

target_include_directories(AssimpModels
    PUBLIC include
)

target_link_libraries(AssimpModels
    GLEW::glew_s
    glfw
    gli
    glm
    assimp
)

# WORK WITH SHADER FILES

add_custom_target(MonoShaders
    COMMENT "Edit shader files"
    SOURCES "shaders/Viewer3D.vert" "shaders/Viewer3D.frag"
            "shaders/LitEnv.vert" "shaders/LitEnv.frag"
            "shaders/OriginalDiffuse.vert" "shaders/OriginalDiffuse.frag"
            "shaders/SimpleDiffuse.vert" "shaders/SimpleDiffuse.frag"
)

set(OUTPUT_SHADER_LIST)
foreach(current_shader "Viewer3D.vert" "Viewer3D.frag"
                       "LitEnv.vert" "LitEnv.frag"
                       "OriginalDiffuse.vert" "OriginalDiffuse.frag"
                       "SimpleDiffuse.vert" "SimpleDiffuse.frag"
)
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${current_shader}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/shaders/${current_shader}"
        COMMAND ${GLSLC_EXE} ARGS "${CMAKE_CURRENT_LIST_DIR}/shaders/${current_shader}" -S -g --target-env=opengl -x glsl
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

add_dependencies(LookAhead Shaders)
add_dependencies(Scene360 Shaders)
add_dependencies(GoodCamera Shaders)
add_dependencies(PlatformTexture Shaders)
add_dependencies(Redesign Shaders)
add_dependencies(LightFix Shaders)

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
                         "Wood_2.KTX"
                         "Illusions.KTX"
)

foreach(current_texture ${TEXTURES_KTX})
    add_custom_command(TARGET GoodCamera
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_LIST_DIR}/${TEXTURES_KTX_DIR}/${current_texture}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${TEXTURES_KTX_DIR}/${current_texture}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/${TEXTURES_KTX_DIR}/${current_texture}"    
    )
endforeach(current_texture)
