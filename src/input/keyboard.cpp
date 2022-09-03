#include "precompiled.h"
#include "keyboard.h"

namespace {
	Keyboard* g_keyboard;
}

Keyboard* Keyboard::get() {
	return g_keyboard;
}

void Keyboard::initialize() {
	g_keyboard = new Keyboard;
}

void Keyboard::deinitialize() {
	delete g_keyboard;
}

Keyboard::Keyboard()
	: IInputMethod(0xFF) {
}

void Keyboard::update() {
}