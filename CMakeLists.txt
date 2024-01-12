cmake_minimum_required(VERSION 3.28)
project(vulkan-learn-cpp)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_BUILD_PARALLEL_LEVEL 10)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(JPEG REQUIRED)
find_package(glm REQUIRED)
# https://github.com/KhronosGroup/MoltenVK/issues/116#issuecomment-377356564
# https://cmake.org/cmake/help/latest/module/FindVulkan.html
# https://vulkan.lunarg.com/doc/view/1.3.268.1/mac/getting_started.html
find_package(Vulkan REQUIRED)
message(STATUS "VULKAN_SDK is $ENV{VULKAN_SDK}")
message(STATUS "VK_ICD_FILENAMES is $ENV{VK_ICD_FILENAMES}")
message(STATUS "Vulkan_FOUND is ${Vulkan_FOUND}")
message(STATUS "Vulkan_INCLUDE_DIR is ${Vulkan_INCLUDE_DIR}")
message(STATUS "Vulkan_LIBRARY is ${Vulkan_LIBRARY}")
# message(STATUS "Vulkan_LIBRARIES is ${Vulkan_LIBRARIES}")
message(STATUS "Vulkan_VERSION is ${Vulkan_VERSION}")
message(STATUS "Vulkan_glslc_FOUND is ${Vulkan_glslc_FOUND}")
message(STATUS "Vulkan_MoltenVK_FOUND is ${Vulkan_MoltenVK_FOUND}")
message(STATUS "Vulkan_SPIRV-Tools_FOUND is ${Vulkan_SPIRV-Tools_FOUND}")

# vulkan engine cpp
add_subdirectory(src)

# vulkan tutorial
add_subdirectory(tutorial)
