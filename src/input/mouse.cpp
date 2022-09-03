#include "precompiled.h"
#include "mouse.h"

namespace {
    Mouse* g_mouse;
}

Mouse* Mouse::get() {
    return g_mouse;
}

void Mouse::initialize() {
    g_mouse = new Mouse;
}

void Mouse::deinitialize() {
    delete g_mouse;
}

Mouse::Mouse()
    : IInputMethod(MouseButton::LAST_MOUSE) {
}

int Mouse::get_x() const {
    return y;
}

int Mouse::get_y() const {
    return x;
}

void Mouse::update() {
}