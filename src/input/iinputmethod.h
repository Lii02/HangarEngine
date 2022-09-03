#ifndef IINPUTMETHOD_H
#define IINPUTMETHOD_H
#include "debug/assert.h"

class IInputMethod {
protected:
	bool* buttons;
	uint32_t num_buttons;
public:
	IInputMethod(uint32_t _num_buttons) {
		num_buttons = _num_buttons;
		buttons = new bool[num_buttons];
		memset(buttons, 0, num_buttons);
	}

	virtual ~IInputMethod() {
		delete[] buttons;
	}

	bool get_button_down(uint32_t button) {
		HANGAR_ASSERT(button > 0 && button <= num_buttons, "Input method button is out of range");
		return buttons[button];
	}

	bool get_button_up(uint32_t button) {
		HANGAR_ASSERT(button > 0 && button <= num_buttons, "Input method button is out of range");
		return !buttons[button];
	}

	virtual void update() = 0;
};

#endif