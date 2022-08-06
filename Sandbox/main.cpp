#include <Hangar/Precompiled.h>
#include <Hangar/Platform/GameWindow.h>
#include <Hangar/Platform/Mouse.h>
#include <Hangar/Platform/Keyboard.h>
#include "Hangar/Debug/Logger.h"

int main(int argc, char** argv) {
	GameWindow window = GameWindow("Hangar Engine", 1280, 720, false);
	window.Open();

	while (window.IsRunning()) {
		window.Poll();
	}

	return 0;
}