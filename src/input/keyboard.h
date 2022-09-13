#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "iinputmethod.h"

class SystemWindow;

typedef SDL_KeyCode HKeyCode;

class Keyboard : public IInputMethod {
	friend class SystemWindow;
private:
public:
	static Keyboard* get();
	static void initialize();
	static void deinitialize();

	Keyboard();

	virtual void update() override;
};

#endif