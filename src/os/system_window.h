#ifndef SYSTEM_WINDOW_H
#define SYSTEM_WINDOW_H
#include "string/astring.h"
#include "math/vectors.h"

enum {
	SYSTEM_WINDOW_RESIZABLE = HANGAR_BIT(0),
	SYSTEM_WINDOW_FULLSCREEN = HANGAR_BIT(1),
	SYSTEM_WINDOW_VULKAN = HANGAR_BIT(2),
	SYSTEM_WINDOW_BORDERLESS = HANGAR_BIT(3),
};

class Keyboard;
class Mouse;

class SystemWindow {
	friend class Keyboard;
	friend class Mouse;
protected:
	bool is_running;
	AString title;
	Vector2 dimensions;
	SDL_Window* window;
	uint8_t flags;
public:
	static SystemWindow* get_singleton();

	SystemWindow(AString _title, uint32_t _width, uint32_t _height, uint8_t _flags);
	virtual ~SystemWindow() { }

	bool get_is_running() const;
	AString get_title() const;
	Vector2 get_dimensions();
	void set_dimensions(Vector2 new_dimensions);
	void set_title(AString new_title);
	void open();
	void close();
	void poll();
	void* get_window_handle();
	bool is_focus();
};

#endif