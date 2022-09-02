#include "precompiled.h"
#include "system_window.h"
#include "debug/assert.h"
#include <SDL2/SDL_syswm.h>

namespace {
	SystemWindow* singleton;
}

SystemWindow* SystemWindow::get_singleton() {
	return singleton;
}

SystemWindow::SystemWindow(AString _title, uint32_t _width, uint32_t _height, uint8_t _flags) {
	title = _title;
	dimensions = Vector2(_width, _height);
	flags = _flags;
	singleton = this;
}

bool SystemWindow::get_is_running() const {
	return is_running;
}

AString SystemWindow::get_title() const {
	return title;
}

Vector2 SystemWindow::get_dimensions() {
	Vector2 dim;
	return dim;
}

void SystemWindow::set_dimensions(Vector2 new_dimensions) {
	dimensions = new_dimensions;
}

void SystemWindow::set_title(AString new_title) {
	title = new_title;
}

void SystemWindow::open() {
	uint32_t sdl_flags = SDL_WINDOW_SHOWN;
	if (flags & SYSTEM_WINDOW_RESIZABLE)
		sdl_flags |= SDL_WINDOW_RESIZABLE;
	if (flags & SYSTEM_WINDOW_VULKAN)
		sdl_flags |= SDL_WINDOW_VULKAN;
	if (flags & SYSTEM_WINDOW_BORDERLESS)
		sdl_flags |= SDL_WINDOW_BORDERLESS;
	window = SDL_CreateWindow(title.ptr(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimensions.x, dimensions.y, sdl_flags);
	HANGAR_ASSERT(window != nullptr, SDL_GetError());
	if (flags & SYSTEM_WINDOW_FULLSCREEN)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	is_running = true;
}

void SystemWindow::close() {
	SDL_DestroyWindow(window);
}

void SystemWindow::poll() {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		}
	}
}

void* SystemWindow::get_window_handle() {
#ifdef HANGAR_WINDOWS
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	return wmInfo.info.win.window;
#endif
}

bool SystemWindow::is_focus() {
	return false;
}