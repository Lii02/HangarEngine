#include <Hangar/Precompiled.h>
#include <Hangar/Platform/GameWindow.h>

int main(int argc, char** argv) {
	GameWindow window = GameWindow("Hangar Engine", 1280, 720);
	window.Open();

	while (window.IsRunning()) {
		window.Poll();
	}

	return 0;
}