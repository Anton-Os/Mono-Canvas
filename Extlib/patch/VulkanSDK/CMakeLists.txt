cmake_minimum_required(VERSION 3.5)

if(TOOLCHAIN_PREFIX)
	set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
	set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
endif(TOOLCHAIN_PREFIX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 11)

project(vulkan-sdk VERSION 1.0 LANGUAGES CXX C)

if(CMAKE_COMPILER_IS_GNUCXX OR (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang"))
	message("Compiler is GNU compatible.")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-missing-field-initializers -Wno-unused-function -Wno-unused-variable -DVK_PROTOTYPES=1 -pthread")
elseif(MSVC)
	message("Compiler is MSVC.")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS /wd4267 /wd4244 /wd4146")
endif()

if(NOT PLATFORM)
	set(PLATFORM png)
endif(NOT PLATFORM)

install(FILES "${CMAKE_SOURCE_DIR}/include/vulkan/vk_platform.h" "${CMAKE_SOURCE_DIR}/include/vulkan/vulkan.h"
	DESTINATION inlcude/VulkanSDK/vulkan
)

# # # # # FRAMEWORK

file(GLOB framework-sources framework/*.cpp)
file(GLOB framework-sources-headers framework/*.hpp)
file(GLOB framework-device-sources framework/device/*.cpp)
file(GLOB framework-device-sources-headers framework/device/*.hpp)
add_library(framework STATIC
	${sources}
	${framework-sources-headers}
	${framework-device-sources}
	${framework-device-sources-headers}
)

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/framework/glm/glm/glm.hpp)
	message(FATAL_ERROR "GLM submodule has not been checked out in framework/glm, please run git submodule init and git submodule update first.")
endif()
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/framework/stb/stb_image.h)
	message(FATAL_ERROR "STB submodule has not been checked out in framework/stb, please run git submodule init and git submodule update first.")
endif()

set(VK_FRAMEWORK_PATHS)
list(APPEND VK_FRAMEWORK_PATHS 
	"framework"
	"framework/stb"
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/${VK_FRAMEWORK_PATHS}
	DESTINATION "${CMAKE_INSTALL_PREFIX}/include/VulkanSDK/${VK_FRAMEWORK_PATHS}"
	FILES_MATCHING PATTERN "*.hpp"
)

# target_include_directories(framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/framework ${CMAKE_CURRENT_SOURCE_DIR}/framework/glm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# We have already built GLM so we can just link to preinstalled version
target_include_directories(framework PUBLIC ${CMAKE_INSTALL_PREFIX}/include/VulkanSDK ${CMAKE_INSTALL_PREFIX}/include/glm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(framework vulkan-stub)

# # # # # PLATFORM

file(GLOB platform-sources-headers platform/*.hpp)

set(VK_OS_NAMES)
list(APPEND VK_OS_NAMES
	"android" 
	"display" 
	"os" 
	"png" 
	"wayland" 
	# "wsi" 
	# "xcb"
)

set(VK_OS_PATHS)
list(APPEND VK_OS_PATHS 
	"platform"
	"platform/android" 
	"platform/display" 
	"platform/os" 
	"platform/png" 
	"platform/wayland" 
	"platform/wsi" 
	"platform/xcb"
)

foreach(os_name ${VK_OS_NAMES})
	message(STATUS "Current OS is ${os_name}")
	file(GLOB current_os_sources platform/${os_name}/*.cpp)
	file(GLOB current_os_headers platform/${os_name}/*.hpp)
	install(FILES ${current_os_headers}
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include/VulkanSDK/${os_name}"
	)
	add_library("platform-${os_name}" STATIC ${current_os_sources})
	message(STATUS "Platform full name is platform-${os_name}")
	target_include_directories("platform-${os_name}" 
		PUBLIC "${CMAKE_INSTALL_PREFIX}/include/VulkanSDK/${os_name}"
		PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/stub ${CMAKE_SOURCE_DIR}/platform
	)
endforeach(os_name)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/platform
	DESTINATION "${CMAKE_INSTALL_PREFIX}/include/VulkanSDK"
	FILES_MATCHING PATTERN "*.hpp"
)

add_library(platform STATIC   .dummy.cpp ${platform-sources-headers})
add_library(platform-wsi STATIC   platform/wsi/wsi.cpp platform/wsi/wsi.hpp)
add_library(platform-asset-manager STATIC   platform/asset_manager.cpp platform/asset_manager.hpp)

if (${CMAKE_BUILD_TYPE} MATCHES "Rel")
    target_compile_definitions(platform-wsi PRIVATE FORCE_NO_VALIDATION=1)
endif()

# add_subdirectory("./platform/${PLATFORM}")

install(DIRECTORY ${CMAKE_SOURCE_DIR}/${VK_OS_PATHS}
	DESTINATION "${CMAKE_INSTALL_PREFIX}/include/VulkanSDK/${VK_OS_PATHS}"
	FILES_MATCHING PATTERN "*.hpp"
)

target_include_directories(platform
	PUBLIC ${CMAKE_INSTALL_PREFIX}/include/VulkanSDK
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# It can be set to anything later
target_link_libraries(platform framework platform-${PLATFORM})
target_link_libraries(platform-wsi vulkan-stub)
target_link_libraries(platform-asset-manager framework)

# # # # # STUB

file(GLOB stub-sources stub/*.cpp)
file(GLOB stub-sources-headers stub/*.hpp)
add_library(vulkan-stub STATIC
	${stub-sources}
	${stub-sources-headers}
)

install(FILES "${CMAKE_SOURCE_DIR}/stub/libvulkan-stub.h"
	DESTINATION inlcude/VulkanSDK
)

target_include_directories(vulkan-stub PUBLIC ${CMAKE_INSTALL_PREFIX}/include/VulkanSDK)
target_link_libraries(vulkan-stub platform)

# # # # # HELLO MY LOVLIES

set(sources-os)
if (UNIX AND (NOT ANDROID))
	set(sources-os platform/os/linux.cpp platform/os/linux.hpp)
elseif(WIN32)
	set(sources-os platform/os/windows.cpp platform/os/windows.hpp)
endif(UNIX AND (NOT ANDROID))

add_library(vulkan-sdk STATIC .dummy.cpp ${sources-os})
target_link_libraries(vulkan-sdk platform)

# # # # # INSTALL STEP TARGET EXPORT

install(TARGETS vulkan-sdk framework platform vulkan-stub "platform-${PLATFORM}"
	EXPORT vulkan_SDK_Targets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
)

install(EXPORT vulkan_SDK_Targets
	FILE vulkan_SDK_Targets.cmake
	DESTINATION lib/cmake/VulkanSDK
)

EXPORT(EXPORT vulkan_SDK_Targets
	FILE vulkan_SDK_Targets.cmake
)


if (UNIX)
	target_link_libraries(vulkan-sdk -ldl -pthread)
endif(UNIX)

include(Sample.cmake)
enable_testing()
add_subdirectory(samples)

