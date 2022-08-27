#include "precompiled.h"
#include "platform/entry_point.h"
#include "debug/logger.h"
#include "threading/thread.h"
#include "threading/mutex.h"

void Main(ArgumentPacket args) {
	Logger::initialize();
	Logger::deinitialize();
	system("pause");
}