
#include <iostream>
#include <vulkan/vulkan.h>

class VulkanRender {
public:
    void run() {
        initVulkan();
        mainLoop();
    }
private:
    void initVulkan();
    void mainLoop();
}