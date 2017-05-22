add_executable(Basis-Triangles Basis.cpp LoadShaders.cpp)

# set_property(TARGET testing123
#    PROPERTY COMPILE_DEFINITIONS FREEGLUT_STATIC
# )

target_include_directories(Basis-Triangles
    PUBLIC ${GLEW_INCLUDE_DIR}
    PUBLIC ${FREEGLUT_INCLUDE_DIRS}
)

target_link_libraries(Basis-Triangles
    GLEW::glew_s
    freeglut
)

# set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/../Installation")

# message("Binary Directory inside Triangles_Basis - - - - - > ${CMAKE_BINARY_DIR}")
# message("Install Prefix inside Triangles_Basis - - - - - > ${CMAKE_INSTALL_PREFIX}")
# message("Source Directory inside Triangles_Basis - - - - - > ${CMAKE_SOURCE_DIR}")

#[[ 
file(COPY "${CMAKE_INSTALL_PREFIX}/bin/freeglutd.dll"
          "${CMAKE_SOURCE_DIR}/Triangles_Basis/Shaders/triangles.vert"
          "${CMAKE_SOURCE_DIR}/Triangles_Basis/Shaders/triangles.frag"
     DESTINATION "${EXECUTABLE_OUTPUT_PATH}/Debug"
)
]]#

# file(COPY "${CMAKE_INSTALL_PREFIX}")