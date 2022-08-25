#include "precompiled.h"
#include "keyboard.h"
#include "debug/assert.h"

#ifdef HANGAR_WINDOWS
class Keyboard::Impl {
private:
	bool keys[0xFF];
public:
	Impl() {
		memset(keys, 0, 0xFF);
	}

	inline void process(MessagePacket packet) {
		switch (packet.msg) {
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			keys[packet.wParam] = true;
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			keys[packet.wParam] = false;
			break;
		}
	}

	inline bool get_key(KeyCode code) const {
		HANGAR_ASSERT(code < 0xFF && code > 0, "Key code out of bounds");
		return keys[code];
	}
};
#endif

namespace {
	Keyboard* g_Keyboard;
}

Keyboard*& Keyboard::get() {
	return g_Keyboard;
}

void Keyboard::initialize() {
	g_Keyboard = new Keyboard();
}

void Keyboard::deinitialize() {
	delete g_Keyboard;
}

Keyboard::Keyboard() {
	this->keyboard_impl = new Keyboard::Impl;
}

Keyboard::~Keyboard() {
	delete keyboard_impl;
}

void Keyboard::process(MessagePacket packet) {
	keyboard_impl->process(packet);
}

bool Keyboard::get_key(KeyCode code) const {
	return keyboard_impl->get_key(code);
}