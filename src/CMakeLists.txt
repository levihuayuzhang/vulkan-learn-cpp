# file(GLOB_RECURSE engine_src CONFIGURE_DEPENDS "src/*.cxx" "src/*.hpp")
# add_executable(vulkan-learn-cpp ${engine_src})
aux_source_directory(./ SRC)
add_executable(vulkan-learn-cpp ${SRC})

# include_directories(vulkan-learn-cpp ./include)
target_include_directories(vulkan-learn-cpp PRIVATE ./include ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${JPEG_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${Vulkan_INCLUDE_DIR})
target_link_libraries(vulkan-learn-cpp glfw GLEW::GLEW ${JPEG_LIBRARIES} Vulkan::Vulkan)