#ifndef VULKAN_API_H
#define VULKAN_API_H
#include "../Platform/GameWindow.h"
#include "RenderAPI.h"

class VulkanAPI : public IRenderAPI {
private:
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
public:
	VulkanAPI(GameWindow* windowPtr);
	~VulkanAPI();

	// Inherited via IRenderAPI
	virtual void Initialize() override;
	virtual void DeInitialize() override;

private:
	void CreateInstance();
	void CreateDebugLayer();
};

#endif