#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "ckCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT (VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}


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
    VkDebugUtilsMessengerEXT debugMessenger;
    std::vector<const char*> requestedLayers = {
//            "ass" // debug purpose
    };

    void initWindow(){
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH,HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan(){
        createInstance();
        setupDebugMessenger();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        if(enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }

    void createInstance (){
        if (enableValidationLayers) {
            requestedLayers.emplace_back("VK_LAYER_KHRONOS_validation");
        }

        // check layer support for validation layer
        if (requestedLayers.size() > 0) {
            if (!checkLayerSupport()) {
                throw std::runtime_error("Validation layers requested, but not available!");
            }
        } else {
            std::cout << "\nNo any layers requested..." << "\n";
        }

        // application info
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // get required extensions
        std::vector<const char*> requiredExtensions = getRequiredExtensions();

        // check whether all required extension are available
        checkExtensions(getAvailableExtensions(), requiredExtensions);

        // instance info
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        // set flag for macOS
#ifdef __APPLE__
        createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR; // for newer macOS SDK
#endif
        // extensions
        createInfo.enabledExtensionCount = (std::uint32_t) requiredExtensions.size();
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();


//        if (createInfo.enabledLayerCount > 0) {
//            std::cout << "\nEnabled layers:" << "\n";
//            for (std::uint32_t i = 0; i < createInfo.enabledLayerCount; i++) {
//                std::cout << "\t" << createInfo.ppEnabledLayerNames[i] << "\n";
//            }
//        } else {
//            std::cout << "\nHasn't enable any layers..." << "\n";
//        }

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (enableValidationLayers) {
            // layers
            createInfo.enabledLayerCount = static_cast<std::uint32_t>(requestedLayers.size());
            createInfo.ppEnabledLayerNames = requestedLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }


        // creating instance
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to create instance...");
        }else {
            std::cout << "\nInstance Create Success..." << std::endl;
        }
    }

    std::vector<const char*> getRequiredExtensions(){
        std::vector<const char*> extensions;

        // get glfw required extension
        std::uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        // set required extension
        for (std::uint32_t i = 0; i < glfwExtensionCount; i++) {
            extensions.emplace_back(glfwExtensions[i]);
        }
        /* Since 1.3.216 Vulkan SDK, need add `VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR` to flags
         * and `VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME` to enabled extension name
         */
#ifdef __APPLE__
        extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME); // for newer macOS SDK
#endif
        if (enableValidationLayers) {
            extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

//        requiredExtensions.emplace_back("assHOLE"); // debugging purpose

        return extensions;
    }

    // get available extension
    std::vector<VkExtensionProperties> getAvailableExtensions (){
        std::uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "\nAvailable Extensions:\n";
        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << "\n";
        }

        return extensions;
    }

    // check whether all required extension from glfw is available
    bool checkExtensions (std::vector<VkExtensionProperties> availableExtensions, std::vector<const char*> requiredExtensions) {
        // transform vector<VkExtensionProperties> to vector<const char*>
        std::vector<const char*> availableExtensionNames;
        for (std::uint32_t i = 0; i < availableExtensions.size(); i++) {
            availableExtensionNames.emplace_back(availableExtensions[i].extensionName);
        }

        // print out required extensions
        std::cout << "\nRequired extensions are: " << "\n";
        for (const auto& requiredExtension : requiredExtensions) {

            std::cout << '\t' << requiredExtension << "\n";
        }

        // compare
        std::vector<const char*> notAvailableRequiredExtensions;
        std::vector<const char*> availableRequiredExtensions;
        bool allAvailable = true;
        bool flag;
        for (std::uint32_t i = 0; i < requiredExtensions.size(); i++){
            flag = false;
            for (std::uint32_t j = 0; j < availableExtensionNames.size(); j++){
//                std::cout << requiredExtensions[i] << ":::" << availableExtensionNames[j] << "\n"; // debugging purpose
                if (strcmp(requiredExtensions[i], availableExtensionNames[j]) == 0) {
                    flag = true;
                    allAvailable = allAvailable && flag;
                    break;
                }else {
                    flag = false;
                }
            }
            if (flag == false) {
                allAvailable = allAvailable && flag;
                notAvailableRequiredExtensions.emplace_back(requiredExtensions[i]);
            } else {
                availableRequiredExtensions.emplace_back(requiredExtensions[i]);
            }
        }

        if (allAvailable) {
            std::cout << "\nAll required extensions are available: " << "\n";
            for (const auto& availableRequiredExtension : availableRequiredExtensions){
                std::cout << '\t' << availableRequiredExtension << "\n";
            }
        }else {
            std::cout << "\nThese required extensions are NOT available: " << "\n";
            for (const auto& notAvailableRequiredExtension : notAvailableRequiredExtensions){
                std::cout << '\t' << notAvailableRequiredExtension << "\n";
            }
            throw std::runtime_error("Some above required extensions are NOT available!\n");
        }

        return allAvailable;
    }

    bool checkLayerSupport() {
        std::cout << "\nChecking layer support... " << "\n";

        // print out requested layers
        std::cout << "\nRequested layers are: " << "\n";
        for (const auto& requestedLayer : requestedLayers) {

            std::cout << '\t' << requestedLayer << "\n";
        }

        bool allFounded = true;
        // checking available layers
        std::cout << "\nChecking available layers... " << "\n";
        std::uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        std::cout << "Available layers are:" << "\n";
        for (auto& availableLayer : availableLayers) {
            std::cout << "\t" << availableLayer.layerName << "\n";
        }

        std::vector<const char*> foundedLayerBuf;
        std::vector<const char*> notFoundedLayerBuf;
        for (const char* requestedLayer : requestedLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers){
                if (strcmp(requestedLayer, layerProperties.layerName) == 0) {
                    layerFound = true;
                    foundedLayerBuf.emplace_back(requestedLayer);
                    break;
                }
            }
            if (!layerFound) {
                notFoundedLayerBuf.emplace_back(requestedLayer);
            }
            allFounded = allFounded && layerFound;
        }

        if (allFounded) {
            std::cout << "\nAll founded layers in available list:" << "\n";
            for (auto& foundedLayer : foundedLayerBuf) {
                std::cout << "\t" << foundedLayer << "\n";
            }
            return true;
        } else {
            if (foundedLayerBuf.size() > 0) {
                std::cout << "\nSome founded layers in available list:" << "\n";
                for (auto &foundedLayer: foundedLayerBuf) {
                    std::cout << "\t" << foundedLayer << "\n";
                }
            }

            std::cout << "\nSome layers NOT founded in available list:" << "\n";
            for (auto& notFoundedLayer : notFoundedLayerBuf) {
                std::cout << "\t" << notFoundedLayer << "\n";
            }
            return false;
        }
    }

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {

        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;
    }

    void setupDebugMessenger(){
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        populateDebugMessengerCreateInfo(createInfo);

        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("Failed to set up debug messenger!");
        }

    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageTye,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData){
        std::cerr << "Validation layer: " << pCallbackData -> pMessage << std::endl;

        return VK_FALSE;
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