#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>

namespace mkk{

class MkkWindow {
    public :
        MkkWindow(int w, int h, std::string name);
        ~MkkWindow();

        MkkWindow(const MkkWindow &) = delete;
        MkkWindow &operator = (const MkkWindow &);

        bool shouldClose (){
            return glfwWindowShouldClose(window);
        }

    private:
        void initWindow();

        const int width;
        const int height;
        std::string windowName;

        GLFWwindow *window;
};

}