#include "precompiled.h"
#include "debug/logger.h"
#include "io/file_system.h"
#include "profiler/profiler.h"
#include "threading/thread.h"
#include "os/system.h"
#include "os/system_window.h"

int main(int args, char** argv) {
	Logger::initialize();
	FileSystem::initialize();
	System::initialize();
	Profiler::initialize();
	Profiler* profiler = Profiler::get();
	SystemWindow window = SystemWindow("Hangar Engine", 1280, 720, SYSTEM_WINDOW_RESIZABLE);
	window.open();

	while (window.get_is_running()) {
		window.poll();
	}

	Profiler::deinitialize();
	System::deinitialize();
	FileSystem::deinitialize();
	Logger::deinitialize();
	return 0;
}