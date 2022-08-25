#include "precompiled.h"
#include "mouse.h"

#ifdef HANGAR_WINDOWS
class Mouse::Impl {
private:
	int x, y;
	bool left_button, middle_button, right_button;
public:
	inline void Process(MessagePacket packet) {
		switch (packet.msg) {
		case WM_LBUTTONDOWN:
			this->left_button = true;
			break;
		case WM_LBUTTONUP:
			this->left_button = false;
			break;
		case WM_MBUTTONDOWN:
			this->middle_button = true;
			break;
		case WM_MBUTTONUP:
			this->middle_button = false;
			break;
		case WM_RBUTTONDOWN:
			this->right_button = true;
			break;
		case WM_RBUTTONUP:
			this->right_button = false;
			break;
		case WM_MOUSEMOVE:
			x = GET_X_LPARAM(packet.lParam);
			y = GET_Y_LPARAM(packet.lParam);
			break;
		}
	}

	inline int get_x() const {
		return x;
	}

	inline int get_y() const {
		return y;
	}

	inline bool is_left_down() const {
		return left_button;
	}

	inline bool is_middle_down() const {
		return middle_button;
	}

	inline bool is_right_down() const {
		return right_button;
	}

	inline void show() {
		ShowCursor(true);
	}

	inline void hide() {
		ShowCursor(false);
	}
};
#endif

namespace {
	Mouse* g_Mouse;
}

Mouse*& Mouse::get() {
	return g_Mouse;
}

void Mouse::initialize() {
	g_Mouse = new Mouse();
}

void Mouse::deinitialize() {
	delete g_Mouse;
}

Mouse::Mouse() {
	mouse_impl = new Mouse::Impl;
}

Mouse::~Mouse() {
	delete mouse_impl;
}

void Mouse::process(MessagePacket packet) {
	mouse_impl->Process(packet);
}

int Mouse::get_x() const {
	return mouse_impl->get_x();
}

int Mouse::get_y() const {
	return mouse_impl->get_y();
}

bool Mouse::is_left_down() const {
	return mouse_impl->is_left_down();
}

bool Mouse::is_middle_down() const {
	return mouse_impl->is_middle_down();
}

bool Mouse::is_right_down() const {
	return mouse_impl->is_right_down();
}

void Mouse::show() {
	mouse_impl->show();
}

void Mouse::hide() {
	mouse_impl->hide();
}