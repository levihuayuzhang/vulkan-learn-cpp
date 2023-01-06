#include <mkk_window.hpp>
#include <stdexcept>

namespace mkk {
    MkkWindow::MkkWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
        initWindow();
    }

    MkkWindow::~MkkWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void MkkWindow::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    }

    void MkkWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("Fail to create window surface...");
        }
    }
}
