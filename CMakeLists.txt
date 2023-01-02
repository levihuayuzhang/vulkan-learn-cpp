cmake_minimum_required(VERSION 3.24)
project(vulkan-learn-cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_PARALLEL_LEVEL 16)

include_directories(vulkan-learn-cpp src/include)
file(GLOB_RECURSE all_src CONFIGURE_DEPENDS "*.cxx")

add_executable(vulkan-learn-cpp ${all_src})

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(JPEG REQUIRED)
find_package(glm REQUIRED)
find_package(Vulkan REQUIRED)


target_include_directories(vulkan-learn-cpp PRIVATE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${JPEG_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${VULKAN_INLCUDE_DIR})
target_link_libraries(vulkan-learn-cpp glfw GLEW::GLEW ${JPEG_LIBRARIES} Vulkan::Vulkan)