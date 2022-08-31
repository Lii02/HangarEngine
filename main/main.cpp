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
	SystemWindow* window = SystemWindow::create("Title", 1280, 720, false);
	window->open();

	while (window->is_running()) {
		window->poll();
	}
	
	delete window;
	Profiler::deinitialize();
	System::deinitialize();
	FileSystem::deinitialize();
	Logger::deinitialize();
	return 0;
}