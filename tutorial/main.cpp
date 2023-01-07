//#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

class HelloTriangleApplication {
public:
    void run () {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    const std::uint32_t WIDTH = 800;
    const std::uint32_t HEIGHT = 600;
    GLFWwindow* window;

    VkInstance instance;


    void initWindow(){
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH,HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan(){
        createInstance();
    }

    void createInstance (){
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        std::uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        /* Since 1.3.216 Vulkan SDK, need add `VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR` to flags
         * and `VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME` to enabled extension name
         */
        std::vector<const char*> requiredExtensions; // use vector handle extensions
        for (std::uint32_t i = 0; i < glfwExtensionCount; i++) {
            requiredExtensions.emplace_back(glfwExtensions[i]);
        }
        requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        createInfo.enabledExtensionCount = (std::uint32_t) requiredExtensions.size();
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();
        createInfo.enabledLayerCount =0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to create instance...");
        }else if (result == VK_SUCCESS) {
            std::cout << "Instance create success at: "<< printf("%p", &instance) << std::endl;
        }
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        glfwDestroyWindow(window);

        glfwTerminate();
    }
};

int main () {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}