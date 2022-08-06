#include "Precompiled.h"
#include "Mouse.h"

#ifdef HANGAR_WINDOWS
class Mouse::Impl {
private:
	int mouseX, mouseY;
	bool leftButton, middleButton, rightButton;
public:
	inline void Process(MessagePacket packet) {
		switch (packet.msg) {
		case WM_LBUTTONDOWN:
			this->leftButton = true;
			break;
		case WM_LBUTTONUP:
			this->leftButton = false;
			break;
		case WM_MBUTTONDOWN:
			this->middleButton = true;
			break;
		case WM_MBUTTONUP:
			this->middleButton = false;
			break;
		case WM_RBUTTONDOWN:
			this->rightButton = true;
			break;
		case WM_RBUTTONUP:
			this->rightButton = false;
			break;
		case WM_MOUSEMOVE:
			mouseX = GET_X_LPARAM(packet.lParam);
			mouseY = GET_Y_LPARAM(packet.lParam);
			break;
		}
	}

	inline int GetX() const {
		return mouseX;
	}

	inline int GetY() const {
		return mouseY;
	}

	inline bool IsLeftDown() const {
		return leftButton;
	}

	inline bool IsMiddleDown() const {
		return middleButton;
	}

	inline bool IsRightDown() const {
		return rightButton;
	}

	inline void ShowMouseCursor() {
		ShowCursor(true);
	}

	inline void HideMouseCursor() {
		ShowCursor(false);
	}
};
#endif

namespace {
	Mouse g_Mouse;
}

Mouse& Mouse::Get() {
	return g_Mouse;
}

Mouse::Mouse() {
	mouseImplementation = new Mouse::Impl;
}

Mouse::~Mouse() {
	delete mouseImplementation;
}

void Mouse::Process(MessagePacket packet) {
	mouseImplementation->Process(packet);
}

int Mouse::GetX() const {
	return mouseImplementation->GetX();
}

int Mouse::GetY() const {
	return mouseImplementation->GetY();
}

bool Mouse::IsLeftDown() const {
	return mouseImplementation->IsLeftDown();
}

bool Mouse::IsMiddleDown() const {
	return mouseImplementation->IsMiddleDown();
}

bool Mouse::IsRightDown() const {
	return mouseImplementation->IsRightDown();
}

void Mouse::ShowMouseCursor() {
	mouseImplementation->ShowMouseCursor();
}

void Mouse::HideMouseCursor() {
	mouseImplementation->HideMouseCursor();
}