cmake_minimum_required(VERSION 3.24)
project(vulkan-learn-cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_PARALLEL_LEVEL 10)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(JPEG REQUIRED)
find_package(glm REQUIRED)
find_package(Vulkan REQUIRED)

# vulkan engine cpp
file(GLOB_RECURSE engine_src CONFIGURE_DEPENDS "src/*.cxx" "src/*.hpp")
add_executable(vulkan-learn-cpp ${engine_src})

include_directories(vulkan-learn-cpp src/include)
target_include_directories(vulkan-learn-cpp PRIVATE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${JPEG_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${VULKAN_INLCUDE_DIR})
target_link_libraries(vulkan-learn-cpp glfw GLEW::GLEW ${JPEG_LIBRARIES} Vulkan::Vulkan)

# vulkan tutorial
file(GLOB_RECURSE t_src "tutorial/*.cpp" "tutorial/*.hpp")
add_executable(vulkan-tutorial ${t_src})

include_directories(vulkan-tutorial tutorial/include)
target_include_directories(vulkan-tutorial PRIVATE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${JPEG_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${VULKAN_INLCUDE_DIR})
target_link_libraries(vulkan-tutorial glfw GLEW::GLEW ${JPEG_LIBRARIES} Vulkan::Vulkan)
