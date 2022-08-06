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
	VkFormat swapchainFormat;
	VkExtent2D swapchainExtent;
	std::vector<VkImage> swapchainImages;
	std::vector<VkImageView> swapchainImageViews;
	VkRenderPass renderPass;
	std::vector<VkFramebuffer> framebuffers;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	uint32_t currentFrame = 0;
	uint32_t imageIndex;
public:
	VulkanAPI(GameWindow* windowPtr, std::vector<const char*> deviceExtensions);
	~VulkanAPI();

	// Inherited via IRenderAPI
	virtual void Initialize() override;
	virtual void DeInitialize() override;
	virtual void BeginFrame(float clearColor[4]) override;
	virtual void EndFrame() override;
private:
	void CreateInstance();
	void CreateDebugLayer();
	void PickPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapchain();
	void CreateImageViews();
	VkRenderPass CreateRenderPass();
	void CreateFramebuffers();
	void CreateCommandPool();
	void CreateCommandBuffers();
	void CreateSync();
};

#endif