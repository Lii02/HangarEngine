#include "Precompiled.h"
#include "GameWindow.h"
#include "Mouse.h"
#include "Keyboard.h"

#ifdef HANGAR_WINDOWS
LRESULT MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	LRESULT defaultProc = DefWindowProc(hwnd, msg, wParam, lParam);
	auto window = reinterpret_cast<GameWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (!window)
		return defaultProc;

	Mouse::Get()->Process({ hwnd, msg, wParam, lParam });
	Keyboard::Get()->Process({ hwnd, msg, wParam, lParam });

	switch (msg) {
	case WM_SIZE:
		if(window->resize != nullptr)
			window->resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return defaultProc;
}

class GameWindow::Impl {
private:
	HWND handle;
	HINSTANCE hinstance;
	bool polling;
public:
	inline void Open(std::string title, uint32_t width, uint32_t height, bool isResizable) {
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
		DWORD styles;
		if (isResizable)
			styles = WS_OVERLAPPEDWINDOW;
		else
			styles = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
		handle = CreateWindowEx(0, className, nullptr, styles, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hinstance, this);
		ShowWindow(handle, SW_NORMAL);
		SetTitle(title);

		SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
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

	inline bool IsPolling() const { 
		return polling;
	}

	inline bool IsFocus() const {
		return GetActiveWindow() == handle;
	}

	inline WindowHandle GetHandle() {
		return handle;
	}
};
#endif

GameWindow::GameWindow(std::string title, uint32_t width, uint32_t height, bool isResizable) {
	this->title = title;
	this->width = width;
	this->height = height;
	this->isResizable = isResizable;
	this->windowImpl = new GameWindow::Impl;
}

GameWindow::~GameWindow() {
	Close();
	delete windowImpl;
}

void GameWindow::Open() {
	windowImpl->Open(title, width, height, isResizable);
	this->isRunning = true;
}

void GameWindow::Close() {
	windowImpl->Close();
	this->isRunning = false;
}

void GameWindow::Poll() {
	windowImpl->Poll();
}

void GameWindow::SetTitle(std::string newTitle) {
	this->title = newTitle;
	windowImpl->SetTitle(newTitle);
}

void GameWindow::SetSize(uint32_t width, uint32_t height) {
	this->width = width;
	this->height = height;
	windowImpl->SetSize(width, height);
}

void GameWindow::SetReizeFunction(ResizeFunc func) {
	this->resize = resize;
}

WindowHandle GameWindow::GetHandle() {
	return windowImpl->GetHandle();
}

bool GameWindow::IsRunning() const {
	return windowImpl->IsPolling() && isRunning;
}

bool GameWindow::IsFocus() const {
	return windowImpl->IsFocus();
}