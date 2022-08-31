#include "precompiled.h"
#include "win32_window.h"

LRESULT MessageHandler(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
	LRESULT default_proc = DefWindowProc(hwnd, msg, w_param, l_param);
	auto window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (!window)
		return default_proc;

	switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return default_proc;
}

Win32Window::Win32Window(AString _title, uint32_t _width, uint32_t _height, bool _is_resizable) 
	: SystemWindow(_title, _width, _height, _is_resizable) {
	instance = GetModuleHandle(nullptr);
}

Win32Window::~Win32Window() {
	close();
}

void Win32Window::set_is_resizable(bool _is_resizable) {
	SystemWindow::set_is_resizable(_is_resizable);
}

SystemWindow::Dimensions Win32Window::get_dimensions() {
	SystemWindow::Dimensions dimensions;
	return dimensions;
}

void Win32Window::set_dimensions(SystemWindow::Dimensions new_dimensions) {
	SystemWindow::set_dimensions(new_dimensions);
	SetWindowPos(handle, nullptr, 0, 0, dimensions.width, dimensions.height, SWP_NOREPOSITION | SWP_SHOWWINDOW);
}

void Win32Window::set_title(AString new_title) {
	SystemWindow::set_title(new_title);
	SetWindowTextA(handle, new_title.ptr());
}

void Win32Window::open() {
	is_polling = true;
	const LPCWSTR class_name = L"HangarEngineClass";
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(wc);
	wc.lpszClassName = class_name;
	wc.cbClsExtra = 0;
	wc.hInstance = instance;
	wc.cbWndExtra = 0;
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MessageHandler;
	RegisterClassEx(&wc);
	
	DWORD styles;
	if (is_resizable)
		styles = WS_OVERLAPPEDWINDOW;
	else
		styles = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	handle = CreateWindowEx(0, class_name, nullptr, styles, CW_USEDEFAULT, CW_USEDEFAULT, dimensions.width, dimensions.height, nullptr, nullptr, instance, this);
	ShowWindow(handle, SW_NORMAL);
	set_title(title);
	SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

void Win32Window::close() {
	DestroyWindow(handle);
}

void Win32Window::poll() {
	MSG msg = { };
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			is_polling = false;
	}
}

void* Win32Window::get_window_handle() {
	return (void*)handle;
}

bool Win32Window::is_focus() {
	return GetActiveWindow() == handle;
}