#include "Precompiled.h"
#include "VulkanAPI.h"
#include "../Debug/Logger.h"
#include <optional>
#include <set>

#define MAX_FRAMES_IN_FLIGHT 2

namespace {
	const std::vector<const char*> vulkanValidationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}

	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		func(instance, debugMessenger, pAllocator);
	}

	VkBool32 DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* userData) {
		switch (messageSeverity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			Logger::Warning(callbackData->pMessage);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			Logger::Error(callbackData->pMessage);
			break;
		}
		return VK_FALSE;
	}

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphics, present;

		bool IsComplete() {
			return graphics.has_value() && present.has_value();
		}
	};

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) {
		QueueFamilyIndices indices;
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				indices.graphics = i;

			VkBool32 presentSupport = false;
			VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

			if (presentSupport)
				indices.present = i;

			if (indices.IsComplete())
				break;

			i++;
		}

		return indices;
	}
}

VulkanAPI::VulkanAPI(GameWindow* windowPtr, std::vector<const char*> deviceExtensions)
	: IRenderAPI(windowPtr) {
	this->deviceExtensions = deviceExtensions;
	Initialize();
}

VulkanAPI::~VulkanAPI() {
	DeInitialize();
}

void VulkanAPI::Initialize() {
	CreateInstance();
#ifdef _DEBUG
	CreateDebugLayer();
#endif
	PickPhysicalDevice();
	surface = windowPtr->CreateVulkanSurface(instance);
	CreateLogicalDevice();
	CreateSwapchain();
	CreateImageViews();
	renderPass = CreateRenderPass();
	CreateFramebuffers();
	CreateCommandPool();
	CreateCommandBuffers();
	CreateSync();
}

void VulkanAPI::DeInitialize() {
	vkDeviceWaitIdle(device);
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
		vkDestroyFence(device, inFlightFences[i], nullptr);
	}
	vkDestroyCommandPool(device, commandPool, nullptr);
	for (auto& framebuffer : framebuffers) {
		vkDestroyFramebuffer(device, framebuffer, nullptr);
	}
	vkDestroyRenderPass(device, renderPass, nullptr);
	for (auto& imageView : swapchainImageViews) {
		vkDestroyImageView(device, imageView, nullptr);
	}
	vkDestroySwapchainKHR(device, swapchain, nullptr);
	vkDestroyDevice(device, nullptr);
	vkDestroySurfaceKHR(instance, surface, nullptr);
#ifdef _DEBUG
	DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
#endif
	vkDestroyInstance(instance, nullptr);
}

void VulkanAPI::BeginFrame(float clearColor[4]) {
	vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
	vkResetFences(device, 1, &inFlightFences[currentFrame]);
	
	vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
	vkResetCommandBuffer(commandBuffers[currentFrame], 0);
	VkCommandBufferBeginInfo beginInfo = { };
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	vkBeginCommandBuffer(commandBuffers[currentFrame], &beginInfo);

	VkRenderPassBeginInfo renderPassInfo = { };
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = renderPass;
	renderPassInfo.framebuffer = framebuffers[imageIndex];
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = swapchainExtent;

	VkClearValue clear;
	memcpy(clear.color.float32, clearColor, sizeof(float) * 4);
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clear;

	vkCmdBeginRenderPass(commandBuffers[currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanAPI::EndFrame() {
	vkCmdEndRenderPass(commandBuffers[currentFrame]);
	vkEndCommandBuffer(commandBuffers[currentFrame]);

	VkSubmitInfo submitInfo = { };
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

	VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]);

	VkPresentInfoKHR presentInfo = { };
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { swapchain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;

	vkQueuePresentKHR(presentQueue, &presentInfo);
	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void VulkanAPI::CreateInstance() {
	VkApplicationInfo appInfo = { };
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "HangarEngineApplication";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "HangarEngine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_3;

	VkInstanceCreateInfo info = { };
	info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	info.pApplicationInfo = &appInfo;

	auto extensions = windowPtr->GetVulkanInstExtensions();
#ifdef _DEBUG
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	info.enabledLayerCount = static_cast<uint32_t>(vulkanValidationLayers.size());
	info.ppEnabledLayerNames = vulkanValidationLayers.data();
#else
	info.enabledLayerCount = 0;
#endif

	info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	info.ppEnabledExtensionNames = extensions.data();

	vkCreateInstance(&info, nullptr, &instance);
}

void VulkanAPI::CreateDebugLayer() {
	VkDebugUtilsMessengerCreateInfoEXT info = { };
	info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	info.pfnUserCallback = DebugCallback;
	CreateDebugUtilsMessengerEXT(instance, &info, nullptr, &debugMessenger);
}

void VulkanAPI::PickPhysicalDevice() {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data());

	// TODO: Find best device
	physicalDevice = physicalDevices[0];
}

void VulkanAPI::CreateLogicalDevice() {
	auto indices = FindQueueFamilies(physicalDevice, surface);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { indices.graphics.value(), indices.present.value() };
	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures = { };
	VkDeviceCreateInfo createInfo = { };
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();
#ifdef _DEBUG
	createInfo.enabledLayerCount = static_cast<uint32_t>(vulkanValidationLayers.size());
	createInfo.ppEnabledLayerNames = vulkanValidationLayers.data();
#else
	createInfo.enabledLayerCount = 0;
#endif

	VkResult result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);
	vkGetDeviceQueue(device, indices.graphics.value(), 0, &graphicsQueue);
	vkGetDeviceQueue(device, indices.present.value(), 0, &presentQueue);
}

void VulkanAPI::CreateSwapchain() {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &capabilities);
	uint32_t formatCount;
	result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);
	formats.resize(formatCount);
	result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, formats.data());
	
	VkPresentModeKHR presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	VkSurfaceFormatKHR surfaceFormat = formats[0];
	VkExtent2D extent = capabilities.currentExtent;

	uint32_t imageCount = capabilities.minImageCount + 1;
	if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
		imageCount = capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo = { };
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices indices = FindQueueFamilies(physicalDevice, surface);
	uint32_t queueFamilyIndices[] = { indices.graphics.value(), indices.present.value() };

	if (indices.graphics != indices.present) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	} else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	createInfo.preTransform = capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	result = vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain);
	vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
	swapchainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapchainImages.data());

	this->swapchainFormat = surfaceFormat.format;
	this->swapchainExtent = extent;
}

void VulkanAPI::CreateImageViews() {
	swapchainImageViews.resize(swapchainImages.size());
	for (size_t i = 0; i < swapchainImageViews.size(); i++) {
		VkImageViewCreateInfo createInfo = { };
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = swapchainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = swapchainFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;
		vkCreateImageView(device, &createInfo, nullptr, &swapchainImageViews[i]);
	}
}

VkRenderPass VulkanAPI::CreateRenderPass() {
	VkRenderPass renderPass;
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = swapchainFormat;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = { };
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = { };
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkRenderPassCreateInfo renderPassInfo = { };
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;

	vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass);
	return renderPass;
}

void VulkanAPI::CreateFramebuffers() {
	framebuffers.resize(swapchainImageViews.size());

	for (size_t i = 0; i < swapchainImageViews.size(); i++) {
		VkImageView attachments[] = {
			swapchainImageViews[i]
		};

		VkFramebufferCreateInfo framebufferInfo = { };
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapchainExtent.width;
		framebufferInfo.height = swapchainExtent.height;
		framebufferInfo.layers = 1;

		vkCreateFramebuffer(device, &framebufferInfo, nullptr, &framebuffers[i]);
	}
}

void VulkanAPI::CreateCommandPool() {
	QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(physicalDevice, surface);

	VkCommandPoolCreateInfo poolInfo = { };
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphics.value();

	vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
}

void VulkanAPI::CreateCommandBuffers() {
	commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo allocInfo = { };
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

	vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data());
}

void VulkanAPI::CreateSync() {
	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

	VkSemaphoreCreateInfo semaphoreInfo = { };
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo = { };
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]);
		vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]);
		vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]);
	}
}