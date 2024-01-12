# file(GLOB_RECURSE t_src "tutorial/*.cpp" "tutorial/*.hpp")
# add_executable(vulkan-tutorial ${t_src})
aux_source_directory(. SRC)
add_executable(vulkan-tutorial ${SRC})

# include_directories(vulkan-tutorial tutorial/include)
target_include_directories(vulkan-tutorial PRIVATE ./include ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${JPEG_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${VULKAN_INLCUDE_DIR})
target_link_libraries(vulkan-tutorial glfw GLEW::GLEW ${JPEG_LIBRARIES} Vulkan::Vulkan)