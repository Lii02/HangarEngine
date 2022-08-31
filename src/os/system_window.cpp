#include "precompiled.h"
#include "system_window.h"
#ifdef HANGAR_WINDOWS
#include "platforms/windows/win32_window.h"
#endif

SystemWindow::SystemWindow(AString _title, uint32_t _width, uint32_t _height, bool _is_resizable) {
	title = _title;
	dimensions = { _width, _height };
	is_resizable = _is_resizable;
}

bool SystemWindow::get_is_resizable() const {
	return is_resizable;
}

bool SystemWindow::is_running() const {
	return is_polling;
}

AString SystemWindow::get_title() const {
	return title;
}

void SystemWindow::set_title(AString new_title) {
	title = new_title;
}

void SystemWindow::set_is_resizable(bool _is_resizable) {
	is_resizable = _is_resizable;
}

SystemWindow::Dimensions SystemWindow::get_dimensions() {
	return dimensions;
}

void SystemWindow::set_dimensions(SystemWindow::Dimensions new_dimensions) {
	dimensions = new_dimensions;
}

SystemWindow* SystemWindow::create(AString title, uint32_t width, uint32_t height, bool is_resizable) {
#ifdef HANGAR_WINDOWS
	return new Win32Window(title, width, height, is_resizable);
#endif
	return nullptr;
}