#include <iostream>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv){
    VkApplicationInfo vulkanPresets = {};
    vulkanPresets.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vulkanPresets.pApplicationName = "Hello Vulkan";
    vulkanPresets.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    vulkanPresets.pEngineName = "None";
    vulkanPresets.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    vulkanPresets.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &vulkanPresets;
    std::cout << "Welcome to Vulkan! " << std::endl;
}