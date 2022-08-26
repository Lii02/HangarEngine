#include "precompiled.h"
#include "game_window.h"
#include "mouse.h"
#include "keyboard.h"

#ifdef HANGAR_WINDOWS
LRESULT message_handler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	LRESULT default_proc = DefWindowProc(hwnd, msg, wParam, lParam);
	auto window = reinterpret_cast<GameWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (!window)
		return default_proc;

	Mouse::get()->process({ hwnd, msg, wParam, lParam });
	Keyboard::get()->process({ hwnd, msg, wParam, lParam });

	switch (msg) {
	case WM_SIZE:
		if(window->resize != nullptr)
			window->resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return default_proc;
}

class GameWindow::Impl {
private:
	HWND handle;
	HINSTANCE hinstance;
	bool polling;
public:
	inline void open(std::string title, uint32_t width, uint32_t height, bool is_resizable) {
		hinstance = GetModuleHandle(NULL);
		polling = true;

		const LPCWSTR className = L"HangarEngineClass";
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.lpszClassName = className;
		wc.cbClsExtra = 0;
		wc.hInstance = hinstance;
		wc.cbWndExtra = 0;
		wc.lpfnWndProc = message_handler;
		wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		RegisterClassEx(&wc);
		DWORD styles;
		if (is_resizable)
			styles = WS_OVERLAPPEDWINDOW;
		else
			styles = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
		handle = CreateWindowEx(0, className, nullptr, styles, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hinstance, this);
		ShowWindow(handle, SW_NORMAL);
		set_title(title);

		SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	}

	inline void close() {
		DestroyWindow(handle);
	}

	inline void poll() {
		MSG msg = { };
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				polling = false;
		}
	}

	inline void set_title(std::string newTitle) {
		SetWindowTextA(handle, newTitle.c_str());
	}

	inline void set_size(uint32_t width, uint32_t height) {
		SetWindowPos(handle, NULL, 0, 0, width, height, SWP_NOREPOSITION | SWP_SHOWWINDOW);
	}

	inline bool is_polling() const { 
		return polling;
	}

	inline bool is_focus() const {
		return GetActiveWindow() == handle;
	}

	inline WindowHandle get_handle() {
		return handle;
	}
};
#endif

GameWindow::GameWindow(std::string _title, uint32_t _width, uint32_t _height, bool _is_resizable) {
	title = _title;
	width = _width;
	height = _height;
	is_resizable = _is_resizable;
	window_impl = new GameWindow::Impl;
}

GameWindow::~GameWindow() {
	close();
	delete window_impl;
}

void GameWindow::open() {
	window_impl->open(title, width, height, is_resizable);
	is_running = true;
}

void GameWindow::close() {
	window_impl->close();
	is_running = false;
}

void GameWindow::poll() {
	window_impl->poll();
}

void GameWindow::set_title(std::string new_title) {
	title = new_title;
	window_impl->set_title(new_title);
}

void GameWindow::set_size(uint32_t new_width, uint32_t new_height) {
	width = new_width;
	height = new_height;
	window_impl->set_size(width, height);
}

void GameWindow::set_resize_function(ResizeFunc resize_function) {
	resize = resize_function;
}

WindowHandle GameWindow::get_handle() {
	return window_impl->get_handle();
}

bool GameWindow::is_window_running() const {
	return window_impl->is_polling() && is_running;
}

bool GameWindow::is_focus() const {
	return window_impl->is_focus();
}