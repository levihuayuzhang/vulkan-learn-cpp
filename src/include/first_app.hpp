#pragma once
#include "mkk_window.hpp"
#include "mkk_pipeline.hpp"

namespace mkk {
class FirstApp {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        void run();

    private:
        MkkWindow mkkWindow {WIDTH, HEIGHT, "Hello Vulkan!!!"};

        MkkPipeline mkkPipeline {"build/simple_shader.vert.spv", "build/simple_shader.frag.spv"};
};
}