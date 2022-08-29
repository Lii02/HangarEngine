#include "precompiled.h"
#include "debug/logger.h"
#include "io/file_system.h"
#include "profiler/profiler.h"
#include "threading/thread.h"
#include "threading/thread_safe.h"

int main(int args, char** argv) {
	Logger::initialize();
	FileSystem::initialize();
	Profiler::initialize();
	Profiler* profiler = Profiler::get();

	Profiler::deinitialize();
	FileSystem::deinitialize();
	Logger::deinitialize();
	Thread::sleep(2500);
	return 0;
}