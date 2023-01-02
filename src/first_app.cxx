#include "first_app.hpp"

namespace mkk {
void FirstApp::run() {
    while(!mkkWindow.shouldClose()) {
        glfwPollEvents();
    }
}
}