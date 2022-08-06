#ifndef VULKAN_API_H
#define VULKAN_API_H
#include "../Platform/GameWindow.h"
#include "RenderAPI.h"

class VulkanAPI : public IRenderAPI {
private:
	std::vector<const char*> deviceExtensions;
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDevice physicalDevice;
	VkSurfaceKHR surface;
	VkDevice device;
	VkQueue graphicsQueue, presentQueue;
	VkSwapchainKHR swapchain;
	std::vector<VkImage> swapchainImages;
public:
	VulkanAPI(GameWindow* windowPtr, std::vector<const char*> deviceExtensions);
	~VulkanAPI();

	// Inherited via IRenderAPI
	virtual void Initialize() override;
	virtual void DeInitialize() override;

private:
	void CreateInstance();
	void CreateDebugLayer();
	void PickPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapchain();
};

#endif