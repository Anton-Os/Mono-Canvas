#[[ add_executable(Singleton
    SingletonTest.cpp
)

target_include_directories(Singleton
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Singleton
    GLEW::glew_s
    glfw
    glm
) #]]