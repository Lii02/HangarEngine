#ifndef VULKAN_API_H
#define VULKAN_API_H
#include "../Platform/GameWindow.h"
#include "IRenderAPI.h"
#include "VMA.h"

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
	uint32_t currentFrame;
	uint32_t imageIndex;

	// Allocations
	VmaAllocator allocator;
public:
	VulkanAPI(GameWindow* windowPtr, std::vector<const char*> deviceExtensions);
	~VulkanAPI();

	// Inherited via IRenderAPI
	virtual void Initialize() override;
	virtual void DeInitialize() override;
	virtual void BeginFrame() override;
	virtual void EndFrame() override;
	virtual uint64_t CreateVertexBuffer(size_t vertexSize, size_t vertexCount, void* data) override;
private:
	void CreateInstance();
	void CreateDebugLayer();
	void PickPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapchain();
	void CreateImageViews();
	void CreateRenderPass();
	void CreateFramebuffers();
	void CreateCommandPool();
	void CreateCommandBuffers();
	void CreateSync();
};

#endif