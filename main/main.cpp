#include "precompiled.h"
#include "debug/logger.h"
#include "io/file_system.h"
#include "profiler/profiler.h"
#include "threading/thread.h"
#include "os/system.h"
#include "os/system_window.h"
#include "input/keyboard.h"
#include "input/mouse.h"

int main(int args, char** argv) {
	Logger::initialize();
	FileSystem::initialize();
	System::initialize();
	Profiler::initialize();
	Keyboard::initialize();
	Mouse::initialize();

	System* sys = System::get();
	Profiler* profiler = Profiler::get();
	Logger* logger = Logger::get();
	FileSystem* fs = FileSystem::get();
	Keyboard* kb = Keyboard::get();
	Mouse* mouse = Mouse::get();

	logger->message("Platform name: " + sys->get_name());
	logger->message("Path: " + sys->get_path());
	logger->message("CPU count: " + AString::int_to_string(sys->get_cpu_count()));
	logger->message("RAM (GB): " + AString::float_to_string(sys->get_ram_mb() / 1024.0f));

	SystemWindow window = SystemWindow("Hangar Engine", 1280, 720, SYSTEM_WINDOW_RESIZABLE | SYSTEM_WINDOW_VULKAN);
	window.open();

	while (window.get_is_running()) {
		window.poll();
	}

	Mouse::deinitialize();
	Keyboard::deinitialize();
	Profiler::deinitialize();
	System::deinitialize();
	FileSystem::deinitialize();
	Logger::deinitialize();
	return 0;
}