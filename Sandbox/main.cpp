#include "precompiled.h"
#include "platform/entry_point.h"
#include "debug/logger.h"
#include "containers/pair.h"
#include "containers/list.h"

void Main(ArgumentPacket args) {
	Logger::initialize();
	List<int> int_list;
	int_list.push(5);
	Logger::deinitialize();
	system("pause");	
}