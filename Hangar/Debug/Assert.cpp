#include "Precompiled.h"
#include "Assert.h"
#include "Logger.h"

void Hangar::Assert(bool expression, const std::string& msg, const char* file, int64_t line) {
	Logger::Assertion(msg, file, line);
#ifdef HANGAR_WINDOWS
	DebugBreak();
#endif
}