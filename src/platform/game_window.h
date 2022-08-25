#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

typedef void(*ResizeFunc)(uint32_t, uint32_t);
typedef void* WindowHandle;

class GameWindow {
#ifdef HANGAR_WINDOWS
	friend LRESULT message_handler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif
private:
	std::string title;
	uint32_t width, height;
	bool is_running, is_resizable;
	ResizeFunc resize;

	class Impl;
	Impl* window_impl;
public:
	GameWindow(std::string window_title, uint32_t window_width, uint32_t window_height, bool window_is_resizable);
	~GameWindow();
	GameWindow(const GameWindow&) = delete;

	void open();
	void close();
	void poll();
	void set_title(std::string new_title);
	void set_size(uint32_t new_width, uint32_t new_height);
	void set_resize_function(ResizeFunc resize_function);
	WindowHandle get_handle();

	bool is_window_running() const;
	bool is_focus() const;
	inline bool is_window_resizable() { return is_resizable; }
	inline std::string get_title() const { return title; }
	inline const uint32_t get_width() const { return width; }
	inline const uint32_t get_height() const { return height; }
};

#endif