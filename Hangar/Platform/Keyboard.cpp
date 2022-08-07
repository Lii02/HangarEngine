#include "Precompiled.h"
#include "Keyboard.h"
#include "../Debug/Assert.h"

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

	inline bool GetKey(KeyCode code) const {
		HANGAR_ASSERT(code < 0xFF && code > 0, "Key code out of bounds");
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
	this->keyboardImpl = new Keyboard::Impl;
}

Keyboard::~Keyboard() {
	delete keyboardImpl;
}

void Keyboard::Process(MessagePacket packet) {
	keyboardImpl->Process(packet);
}

bool Keyboard::GetKey(KeyCode code) const {
	return keyboardImpl->GetKey(code);
}