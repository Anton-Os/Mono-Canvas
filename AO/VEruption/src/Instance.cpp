#include <iostream>
#include <vector>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace vk100 {
    unsigned int extCount;
    const char** extList;
    VkApplicationInfo Presets = {};
    VkInstanceCreateInfo CreateInfo = {};
    VkInstance Instance;
    VkResult Result;

}

void checkAvailableExt(){
    uint32_t vk100_availableExtCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &vk100_availableExtCount, nullptr);
    std::vector<VkExtensionProperties> vk100_availableExt(vk100_availableExtCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &vk100_availableExtCount, vk100_availableExt.data());
    std::cout << "Available Extensions: " << std::endl;
    for(const VkExtensionProperties& vk100_currentExt : vk100_availableExt)
        std::cout << "\t" << vk100_currentExt.extensionName << std::endl;
}

int main(int argc, const char** argv){
    vk100::extCount = 0;
    vk100::extList = glfwGetRequiredInstanceExtensions(&vk100::extCount);

    if(! glfwInit()){
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window;
    window = glfwCreateWindow(700, 700, argv[0], NULL, NULL);
    if(! window){
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    vk100::Presets.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vk100::Presets.pApplicationName = "Hello Vulkan";
    vk100::Presets.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    vk100::Presets.pEngineName = "None";
    vk100::Presets.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    vk100::Presets.apiVersion = VK_API_VERSION_1_0;

    vk100::CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    vk100::CreateInfo.pApplicationInfo = &vk100::Presets;
    vk100::CreateInfo.enabledExtensionCount = vk100::extCount;
    vk100::CreateInfo.ppEnabledExtensionNames = vk100::extList;

    vk100::Result = vkCreateInstance(&vk100::CreateInfo, nullptr, &vk100::Instance);
    if(vk100::Result != VK_SUCCESS) std::cerr << "Vulkan instance has failed" << std::endl;
    else std::cout << "Vulkan instance succeeded"<< std::endl;

    checkAvailableExt();
    
    // std::cout << "Welcome to Vulkan! " << std::endl;
}