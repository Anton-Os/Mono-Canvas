ADD_EXECUTABLE(Working Prime/Prime-A.cpp)
ADD_EXECUTABLE(Dimentions Prime/Prime-B.cpp)
# ADD_EXECUTABLE(PrimeSetup Prime/Prime-C.cpp)
# ADD_EXECUTABLE(Reserve Reserve/Reserve-A.cpp)
ADD_EXECUTABLE(Reserve Reserve/Reserve-B.cpp)

# ADD_CUSTOM_TARGET(Dimentions-Shaders
#    SOURCES ${SHADER_CONTENTS_DIMENTIONS}/A1.vert
#            ${SHADER_CONTENTS_DIMENTIONS}/A1.frag
#            ${SHADER_CONTENTS_DIMENTIONS}/B1.vert
#            ${SHADER_CONTENTS_DIMENTIONS}/B1.frag
# )

SET(SHADER_CONTENTS_DIMENTIONS "${CMAKE_CURRENT_LIST_DIR}/Shaders" CACHE PATH "Shader Directory for Dimentions" FORCE)
# SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
# SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/DIMENTIONS-BIN")

TARGET_INCLUDE_DIRECTORIES(Working
    PUBLIC ${GLEW_INCLUDE_DIR}
    PUBLIC ${FREEGLUT_INCLUDE_DIRS}
)

TARGET_INCLUDE_DIRECTORIES(Dimentions
    PUBLIC ${GLEW_INCLUDE_DIRS}
    PUBLIC ${FREEGLUT_INCLUDE_DIRS}

    # PUBLIC ${OPENTHREADS_INCLUDE_DIR}
    # PUBLIC ${OPENAL_INCLUDE_DIR}
)

#[[
TARGET_INCLUDE_DIRECTORIES(PrimeSetup
    PUBLIC ${FREEGLUT_INCLUDE_DIRS}
)
]]#

TARGET_INCLUDE_DIRECTORIES(Reserve
    PUBLIC ${FLTK_INCLUDEDIR}
)

TARGET_LINK_LIBRARIES(Working
    GLEW::glew_s
    freeglut
)

TARGET_LINK_LIBRARIES(Dimentions
    GLEW::glew_s
    freeglut
)

#[[
TARGET_LINK_LIBRARIES(PrimeSetup
    GLEW::glew_s
    glfw
)
#]]

TARGET_LINK_LIBRARIES(Reserve 
    SQLite_static
    fltk # fltk_forms # fltk_gl
)

FOREACH(current_shader "A1.vert" "A1.frag")
    ADD_CUSTOM_COMMAND(TARGET Working
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${SHADER_CONTENTS_DIMENTIONS}/${current_shader}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${current_shader}"
        DEPENDS "${SHADER_CONTENTS_DIMENTIONS}/${current_shader}"
    )
ENDFOREACH(current_shader)

FOREACH(current_shader "B1.vert" "B1.frag")
    ADD_CUSTOM_COMMAND(TARGET Dimentions
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${SHADER_CONTENTS_DIMENTIONS}/${current_shader}"
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${current_shader}"
        DEPENDS "${SHADER_CONTENTS_DIMENTIONS}/${current_shader}"
    )
ENDFOREACH(current_shader)
