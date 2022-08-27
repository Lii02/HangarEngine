#include "precompiled.h"
#include "platform/entry_point.h"
#include "debug/logger.h"
#include "containers/pair.h"
#include "containers/list.h"

void Main(ArgumentPacket args) {
	Logger::initialize();
	Logger::deinitialize();
	system("pause");
}