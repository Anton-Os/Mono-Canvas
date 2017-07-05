cmake_minimum_required(VERSION 3.6)
project(SQLite)

add_library(SQLite SHARED "sqlite3.c")
add_library(SQLite_static STATIC "sqlite3.c")
add_executable(sqlite_shell "shell.c")

target_include_directories(SQLite PUBLIC
    $<BUILD_INTERFACE:${SQLITE_PROJECT_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)

if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        set_target_properties(SQLite PROPERTIES DEFINE_SYMBOL "SQLITE_API=__declspec(dllexport)")
endif()

target_include_directories(SQLite_static PUBLIC 
    $<BUILD_INTERFACE:${SQLITE_PROJECT_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)
target_link_libraries(sqlite_shell SQLite_static)

set(sqlite_targets)
list(APPEND sqlite_targets SQLite SQLite_static sqlite_shell)

install(TARGETS ${sqlite_targets}
    EXPORT sqliteTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(EXPORT sqliteTargets
    FILE SQLiteTargets.cmake
    DESTINATION lib/cmake/SQLite 
)

export(EXPORT sqliteTargets
       FILE SQLiteTargets.cmake
)

install(FILES "${CMAKE_SOURCE_DIR}/SQLiteConfig.cmake"
        DESTINATION lib/cmake/SQLite
)

install(FILES "${CMAKE_SOURCE_DIR}/sqlite3.h"
        DESTINATION include
)