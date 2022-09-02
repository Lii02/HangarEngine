#include "precompiled.h"
#include "assert.h"
#include "logger.h"
#include "os/system.h"

void Hangar::assert(bool expression, const char* msg, const char* file, int64_t line) {
	if (!expression) {
		Logger::get()->assertion(msg, file, line);
		System::get()->debug_break();
	}
}