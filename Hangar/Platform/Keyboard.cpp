#include "Precompiled.h"
#include "Keyboard.h"

#ifdef HANGAR_WINDOWS
class Keyboard::Impl {
private:
	bool keys[0xFF];
public:
	Impl() {
		memset(keys, 0, 0xFF);
	}

	inline void Process(MessagePacket packet) {
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

	inline bool GetKey(uint8_t code) const {
		// TODO: Replace this with custom assert
		assert(code > 0 && code < 0xFF);
		return keys[code];
	}
};
#endif

namespace {
	Keyboard g_Keyboard;
}

Keyboard& Keyboard::Get() {
	return g_Keyboard;
}

Keyboard::Keyboard() {
	this->keyboardImplementation = new Keyboard::Impl;
}

Keyboard::~Keyboard() {
	delete keyboardImplementation;
}

void Keyboard::Process(MessagePacket packet) {
	keyboardImplementation->Process(packet);
}

bool Keyboard::GetKey(uint8_t code) const {
	return keyboardImplementation->GetKey(code);
}