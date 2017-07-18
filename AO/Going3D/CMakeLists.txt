add_executable(AssimpModels
    src/LoadTextures.cpp
    src/LoadShaders.cpp
    src/Model3D.cpp
    src/Prime.cpp
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
)

set(OUTPUT_SHADER_LIST)
foreach(current_shader "Viewer3D.vert" "Viewer3D.frag"
                       "LitEnv.vert" "LitEnv.frag"
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

add_dependencies(AssimpModels MonoShaders)

# WORK WITH TEXTURE/IMAGE FILES

set(TEXTURES_KTX)
set(MODELS_3D)
set(TEXTURES_KTX_DIR "data/ktx")
set(MODELS_3D_DIR "data/3D")
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
list(APPEND MODELS_3D "RECARO.stl"
                      "DIE-CASTED-1.stp"
                      "low-poly-mill.max"
                      "low-poly-mill.obj"
)

foreach(current_texture ${TEXTURES_KTX})
    add_custom_command(TARGET AssimpModels
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_LIST_DIR}/${TEXTURES_KTX_DIR}/${current_texture}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${TEXTURES_KTX_DIR}/${current_texture}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/${TEXTURES_KTX_DIR}/${current_texture}"    
    )
endforeach(current_texture)

foreach(current_model ${MODELS_3D})
    add_custom_command(TARGET AssimpModels
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_LIST_DIR}/${MODELS_3D_DIR}/${current_model}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${MODELS_3D_DIR}/${current_model}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/${MODELS_3D_DIR}/${current_model}"
    )
endforeach(current_model)
