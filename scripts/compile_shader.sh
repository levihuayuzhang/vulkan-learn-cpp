#!/usr/bin/env sh
# execute in project root directory
glslc src/shaders/simple_shader.vert -o build/simple_shader.vert.spv
glslc src/shaders/simple_shader.frag -o build/simple_shader.frag.spv