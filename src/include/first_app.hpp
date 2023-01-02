#pragma once
#include "mkk_window.hpp"

namespace mkk {
class FirstApp {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        void run();

    private:
        MkkWindow mkkWindow {WIDTH, HEIGHT, "Hello Vulkan!!!"};
};
}