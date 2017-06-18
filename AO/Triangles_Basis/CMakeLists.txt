add_executable(Basis-Triangles Basis.cpp LoadShaders.cpp)

# target_compile_definitions(Basis-Triangles PUBLIC FREEGLUT_STATIC)

target_include_directories(Basis-Triangles
    PUBLIC ${GLEW_INCLUDE_DIR}
    PUBLIC ${FREEGLUT_INCLUDE_DIRS}
)

target_link_libraries(Basis-Triangles
    GLEW::glew_s
    freeglut_static
)