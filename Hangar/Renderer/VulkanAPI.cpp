#include "Precompiled.h"
#include "VulkanAPI.h"
#include "../Debug/Logger.h"

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
		Logger::Message(callbackData->pMessage);
		return VK_FALSE;
	}
}

VulkanAPI::VulkanAPI(GameWindow* windowPtr)
	: IRenderAPI(windowPtr) {
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
}

void VulkanAPI::DeInitialize() {
#ifdef _DEBUG
	DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
#endif
	vkDestroyInstance(instance, nullptr);
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