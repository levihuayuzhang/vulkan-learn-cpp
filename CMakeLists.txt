cmake_minimum_required(VERSION 3.28)

if (PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(STATUS "WARN: PROJECT_BINARY_DIR == PROJECT_SOURCE_DIR")
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "default set CMAKE_BUILD_TYPE to Release")
    set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "DEBUG MODE")
endif()

if (NOT MSVC)
    find_program(CCACHE_PROGRAM ccache)
    if (CCACHE_PROGRAM)
        message(STATUS "Found CCache: ${CCACHE_PROGRAM}")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
    endif()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_BUILD_PARALLEL_LEVEL 10)

project(vulkan-learn-cpp)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(JPEG REQUIRED)
find_package(glm REQUIRED)
# https://github.com/KhronosGroup/MoltenVK/issues/116#issuecomment-377356564
# https://cmake.org/cmake/help/latest/module/FindVulkan.html
# https://vulkan.lunarg.com/doc/view/1.3.268.1/mac/getting_started.html
find_package(Vulkan
            REQUIRED
            OPTIONAL_COMPONENTS MoltenVK glslc glslangValidator glslang shaderc_combined SPIRV-Tools dxc)
message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")
message(STATUS "APPLE is ${APPLE}")
message(STATUS "VULKAN_SDK is $ENV{VULKAN_SDK}")
message(STATUS "VK_ICD_FILENAMES is $ENV{VK_ICD_FILENAMES}")
message(STATUS "Vulkan_FOUND is ${Vulkan_FOUND}")
message(STATUS "Vulkan_INCLUDE_DIR is ${Vulkan_INCLUDE_DIR}")
message(STATUS "Vulkan_LIBRARY is ${Vulkan_LIBRARY}")
message(STATUS "Vulkan_VERSION is ${Vulkan_VERSION}")
message(STATUS "Vulkan_MoltenVK_FOUND is ${Vulkan_MoltenVK_FOUND}")
message(STATUS "Vulkan_MoltenVK_LIBRARY is ${Vulkan_MoltenVK_LIBRARY}")
message(STATUS "Vulkan_glslc_FOUND is ${Vulkan_glslc_FOUND}")
message(STATUS "Vulkan_glslang_FOUND is ${Vulkan_glslang_FOUND}")
message(STATUS "Vulkan_SPIRV-Tools_FOUND is ${Vulkan_SPIRV-Tools_FOUND}")

include_directories(${Vulkan_INCLUDE_DIR})
# vulkan engine cpp
add_subdirectory(src)
# vulkan tutorial
add_subdirectory(tutorial)
