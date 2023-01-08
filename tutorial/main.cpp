//#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <algorithm>

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
        std::vector<const char*> requiredExtensions; // use vector handle for extensions returned from glfw
        for (std::uint32_t i = 0; i < glfwExtensionCount; i++) {
            requiredExtensions.emplace_back(glfwExtensions[i]);
        }
#ifdef __APPLE__
        requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME); // for newer macOS SDK
#endif
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
#ifdef __APPLE__
        createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR; // for newer macOS SDK
#endif
        createInfo.enabledExtensionCount = (std::uint32_t) requiredExtensions.size();
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();
        createInfo.enabledLayerCount =0;

        // get available extension
        std::vector<VkExtensionProperties> availableExtensions = getAvailableExtensions ();

//todo: check extensions required by glfw is available in vulkan supported extension list
//        std::vector<const char*> availableExtensionNames;
//        for (std::uint32_t i = 0; i < availableExtensions.size(); i++) {
//            availableExtensionNames.emplace_back(availableExtensions[i].extensionName);
//        }
//        bool allAvailable = checkExtensions( availableExtensionNames, requiredExtensions);
//        if (allAvailable) {
//            std::cout << "\n All Required Extensions are all available" << "\n";
//        }

        // creating instance
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to create instance...");
        }else {
            std::cout << "\nInstance Create Success!!!" << std::endl;
        }
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }

    // get available extension
    std::vector<VkExtensionProperties> getAvailableExtensions (){
        std::uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "Available Extensions:\n";
        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << "\n";
        }

        return extensions;
    }

//todo: check extensions required by glfw is available in vulkan supported extension list
//    bool checkExtensions (std::vector<const char*> availableExtensions, std::vector<const char*> requiredExtensions) {
////        std::sort(requiredExtensions.begin(), requiredExtensions.end());
////        std::sort(availableExtensions.begin(), availableExtensions.end());
////        return std::includes(availableExtensions.begin(), availableExtensions.end(),requiredExtensions.begin(), requiredExtensions.end());
//
//        bool allAvailable = false;
//        for (std::uint32_t i = 0; i < requiredExtensions.size(); i++){
//            allAvailable = allAvailable || false;
//            for (std::uint32_t j = 0; j < availableExtensions.size(); j++){
//                if (requiredExtensions[i] == availableExtensions[j]) {
//                    allAvailable = true;
//                    break;
//                }
//            }
//        }
//        return allAvailable;
//    }
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