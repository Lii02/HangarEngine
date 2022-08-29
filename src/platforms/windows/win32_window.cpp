#include "precompiled.h"
#include "win32_window.h"

Win32Window::Win32Window() {
}

Win32Window::~Win32Window() {
}

void Win32Window::set_is_resizable(bool _is_resizable) {
}

SystemWindow::Dimensions Win32Window::get_dimensions() {
	SystemWindow::Dimensions dimensions;
	return dimensions;
}

void Win32Window::set_dimensions(SystemWindow::Dimensions new_dimensions) {
	SystemWindow::set_dimensions(new_dimensions);
}

void Win32Window::set_title(AString new_title) {
	SystemWindow::set_title(new_title);
}

void Win32Window::open() {
}

void Win32Window::close() {
}

void Win32Window::poll() {
}

void* Win32Window::get_window_handle() {
	return (void*)handle;
}