#include "Precompiled.h"
#include "GameWindow.h"

#ifdef HANGAR_WINDOWS
LRESULT MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

class GameWindow::Impl {
private:
	HWND handle;
	HINSTANCE hinstance;
	bool polling;
public:
	inline void Open(std::string title, uint32_t width, uint32_t height) {
		hinstance = GetModuleHandle(NULL);
		polling = true;

		const LPCWSTR className = L"HangarEngineClass";
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.lpszClassName = className;
		wc.cbClsExtra = 0;
		wc.hInstance = hinstance;
		wc.cbWndExtra = 0;
		wc.lpfnWndProc = MessageHandler;
		wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		RegisterClassEx(&wc);

		DWORD styles = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
		handle = CreateWindowEx(0, className, nullptr, styles, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hinstance, this);
		ShowWindow(handle, SW_NORMAL);
		SetTitle(title);
	}

	inline void Close() {
		DestroyWindow(handle);
	}

	inline void Poll() {
		MSG msg = { };
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				polling = false;
		}
	}

	inline void SetTitle(std::string newTitle) {
		SetWindowTextA(handle, newTitle.c_str());
	}

	inline void SetSize(uint32_t width, uint32_t height) {
		SetWindowPos(handle, NULL, 0, 0, width, height, SWP_NOREPOSITION | SWP_SHOWWINDOW);
	}

	inline std::vector<const char*> GetVulkanInstExtensions() const {
		return { VK_KHR_WIN32_SURFACE_EXTENSION_NAME };
	}

	inline VkSurfaceKHR CreateVulkanSurface(VkInstance& instance) {
		VkSurfaceKHR surface;
		VkWin32SurfaceCreateInfoKHR createInfo;
		memset(&createInfo, 0, sizeof(VkWin32SurfaceCreateInfoKHR));
		createInfo.hinstance = hinstance;
		createInfo.hwnd = handle;
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		vkCreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface);
		return surface;
	}

	inline bool IsPolling() const { 
		return polling;
	}
};
#endif

GameWindow::GameWindow(std::string title, uint32_t width, uint32_t height) {
	this->title = title;
	this->width = width;
	this->height = height;
	this->windowImplementation = new GameWindow::Impl;
}

GameWindow::~GameWindow() {
	Close();
	delete windowImplementation;
}

void GameWindow::Open() {
	windowImplementation->Open(title, width, height);
	this->isRunning = true;
}

void GameWindow::Close() {
	windowImplementation->Close();
	this->isRunning = false;
}

void GameWindow::Poll() {
	windowImplementation->Poll();
}

void GameWindow::SetTitle(std::string newTitle) {
	this->title = newTitle;
	windowImplementation->SetTitle(newTitle);
}

void GameWindow::SetSize(uint32_t width, uint32_t height) {
	this->width = width;
	this->height = height;
	windowImplementation->SetSize(width, height);
}

std::vector<const char*> GameWindow::GetVulkanInstExtensions() const {
	return windowImplementation->GetVulkanInstExtensions();
}

VkSurfaceKHR GameWindow::CreateVulkanSurface(VkInstance& instance) {
	return windowImplementation->CreateVulkanSurface(instance);
}

bool GameWindow::IsRunning() const {
	return windowImplementation->IsPolling() && isRunning;
}