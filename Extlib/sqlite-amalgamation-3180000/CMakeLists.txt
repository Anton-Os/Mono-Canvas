cmake_minimum_required(VERSION 3.6)
project(SQLite)

add_library(SQLite SHARED "sqlite3.c")
add_library(SQLite_static STATIC "sqlite3.c")
add_executable(sqlite_shell "shell.c")

target_include_directories(SQLite PUBLIC
    $<BUILD_INTERFACE:${SQLITE_PROJECT_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)

target_include_directories(SQLite_static PUBLIC 
    $<BUILD_INTERFACE:${SQLITE_PROJECT_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)

#[[

target_include_directories(SQLite INTERFACE
    $<BUILD_INTERFACE:${SQLITE_PROJECT_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)

target_include_directories(SQLite_static INTERFACE
    $<BUILD_INTERFACE:${SQLITE_PROJECT_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)
#]]

target_link_libraries(sqlite_shell SQLite_static)

set(sqlite_targets)
list(APPEND sqlite_targets SQLite SQLite_static sqlite_shell)

install(TARGETS ${sqlite_targets}
    EXPORT sqliteTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# install(EXPORT ${sqlite_targets})

install(EXPORT sqliteTargets
    FILE SQLiteTargets.cmake
    DESTINATION lib/cmake/SQLite 
)

#export(TARGETS ${sqlite_targets}
export(EXPORT sqliteTargets
       FILE SQLiteTargets.cmake
       # EXPORT_LINK_INTERFACE_LIBRARIES
       # FILE sqliteTargets.cmake
)

install(FILES "${CMAKE_SOURCE_DIR}/SQLiteConfig.cmake"
        DESTINATION lib/cmake/SQLite
)

install(FILES "${CMAKE_SOURCE_DIR}/sqlite3.h"
        DESTINATION include
)