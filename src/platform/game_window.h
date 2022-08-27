#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include "string/astring.h"

typedef void(*ResizeFunc)(uint32_t, uint32_t);
typedef void* WindowHandle;

class GameWindow {
#ifdef HANGAR_WINDOWS
	friend LRESULT message_handler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif
private:
	AString title;
	uint32_t width, height;
	bool is_running, is_resizable;
	ResizeFunc resize;

	class Impl;
	Impl* window_impl;
public:
	GameWindow(AString _title, uint32_t _width, uint32_t _height, bool _is_resizable);
	~GameWindow();
	GameWindow(const GameWindow&) = delete;

	void open();
	void close();
	void poll();
	void set_title(AString new_title);
	void set_size(uint32_t new_width, uint32_t new_height);
	void set_resize_function(ResizeFunc func);
	WindowHandle get_handle();

	bool is_window_running() const;
	bool is_focus() const;
	inline bool is_window_resizable() { return is_resizable; }
	inline AString get_title() const { return title; }
	inline const uint32_t get_width() const { return width; }
	inline const uint32_t get_height() const { return height; }
};

#endif