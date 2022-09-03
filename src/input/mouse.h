#ifndef MOUSE_H
#define MOUSE_H
#include "iinputmethod.h"

enum MouseButton : int {
	MOUSE_LEFT = SDL_BUTTON_LEFT,
	MOUSE_MIDDLE = SDL_BUTTON_MIDDLE,
	MOUSE_RIGHT = SDL_BUTTON_RIGHT,
	LAST_MOUSE
};

class SystemWindow;

class Mouse : public IInputMethod {
	friend class SystemWindow;
private:
	int x, y;
public:
	static Mouse* get();
	static void initialize();
	static void deinitialize();

	Mouse();

	int get_x() const;
	int get_y() const;

	virtual void update() override;
};

#endif