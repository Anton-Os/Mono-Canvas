# BuildExtlib.cmake configures the build of external libraries and
# provides "BuildExtlibs" cmake target to build external libraries.

include(CMakeParseArguments)
include("Extlib/cmake/WriteInitialCache.cmake")
include("Extlib/cmake/CompilerSettings.cmake")

#
# CreateBuildCMakeProjectTarget creates target with provided name that invokes
# a build of CMake generated build system.
# The options are:
# ALL - if specified then generated target is added to the default build targets
# BINARY_DIR <binary-dir> - provides the location of cmake generated build
# system.
# DEPENDS <dep1> [dep2...] - provides dependencies of generated target.
function(CreateBuildCMakeProjectTarget name)
    set(options ALL)
    set(oneValueArgs BINARY_DIR)
    set(multiValueArgs DEPENDS)
    cmake_parse_arguments(CreateBuildCMakeProjectTarget
        "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN}
    )

    if (NOT CreateBuildCMakeProjectTarget_BINARY_DIR)
        message(FATAL_ERROR "NO BINARY_DIR option provided")
    endif()

    set(all_option)
    if(CreateBuildCMakeProjectTarget_ALL)
        set(all_option ALL)
    endif()

    set(depends_options)
    if (CreateBuildCMakeProjectTarget_DEPENDS)
        set(depends_options DEPENDS ${CreateBuildCMakeProjectTarget_DEPENDS})
    endif()


    if ("${CMAKE_GENERATOR}" MATCHES "Make")
        # Use recursive make (note: following is not ${MAKE}).
     	add_custom_target(${name} ${all_option}
            ${depends_options}
            COMMENT "Building ${CreateBuildCMakeProjectTarget_BINARY_DIR}"
            COMMAND $(MAKE)
            WORKING_DIRECTORY ${CreateBuildCMakeProjectTarget_BINARY_DIR}
        )
    else()
     	add_custom_target(${name} ${all_option}
            ${depends_options}
            COMMENT "Building ${CreateBuildCMakeProjectTarget_BINARY_DIR}"
            COMMAND ${CMAKE_COMMAND}
                --build ${CreateBuildCMakeProjectTarget_BINARY_DIR}
                --config ${CMAKE_CFG_INTDIR}
            WORKING_DIRECTORY ${CreateBuildCMakeProjectTarget_BINARY_DIR}
        )
    endif()
endfunction(CreateBuildCMakeProjectTarget)

#
# Makes ${EXTLIB_BUILD_PATH} directory if not already exists
add_custom_command(
    OUTPUT "${EXTLIB_BUILD_PATH}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${EXTLIB_BUILD_PATH}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

#
# ExtlibConfigure - function configure EXTLIB
function (ExtlibConfigure)
    # Configure the External Libraries
    #
    # extlib_config_cache_file - the initial cache file used to configure
    # External Libraries
    set(extlib_config_cache_file
        "${CMAKE_CURRENT_BINARY_DIR}/ConfigExtlibCache.txt"
    )

    # Write Inital Cache used to configure the External Libraries
    WriteInitialCacheEx(
      OUTPUT_FILE "${extlib_config_cache_file}"
      CMAKE_CACHE_ARGS
          -DEXTLIB_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
          ${EXTLIB_CMAKE_BUILD_TYPE_CACHE_ARG}
          ${EXTLIB_COMPILER_ARGS}
    )

    if (EXISTS "${EXTLIB_BUILD_PATH}/CMakeCache.txt")
        set(extlib_cmake_path "${EXTLIB_BUILD_PATH}")
    else()
        set(extlib_cmake_path "${CMAKE_CURRENT_SOURCE_DIR}/extlib")
    endif()
        
    #
    # ConfigureExtlibs - configure External Libraries target
    # Should this depend on "${extlib_config_cache_file}"?
    add_custom_target(ConfigureExtlibs
        DEPENDS "${EXTLIB_BUILD_PATH}"
        COMMENT "Configuring External Libraries"
        COMMAND ${CMAKE_COMMAND} -C ${extlib_config_cache_file}
            "-G${CMAKE_GENERATOR}" "${extlib_cmake_path}"
        WORKING_DIRECTORY "${EXTLIB_BUILD_PATH}"
    )
        
endfunction(ExtlibConfigure)

# Configure the External Libraries
ExtlibConfigure()

#
# Build External Libraries target
CreateBuildCMakeProjectTarget(BuildExtlibs
    DEPENDS ConfigureExtlibs
    BINARY_DIR "${EXTLIB_BUILD_PATH}"
)
