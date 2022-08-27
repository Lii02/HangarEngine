#include "precompiled.h"
#include "platform/entry_point.h"
#include "debug/logger.h"
#include "io/file_system.h"
#include "profiler/profiler.h"
#include "threading/thread.h"

void Main(ArgumentPacket args) {
	Logger::initialize();
	FileSystem::initialize();
	Profiler::initialize();
	Profiler*& profiler = Profiler::get();

	Profiler::deinitialize();
	FileSystem::deinitialize();
	Logger::deinitialize();
	system("pause");
}