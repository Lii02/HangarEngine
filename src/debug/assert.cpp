#include "precompiled.h"
#include "assert.h"
#include "logger.h"

void Hangar::assert(bool expression, const std::string& msg, const char* file, int64_t line) {
	if (!expression) {
		Logger::assertion(msg, file, line);
#ifdef HANGAR_WINDOWS
		DebugBreak();
#endif
	}
}