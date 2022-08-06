#ifndef HANGAR_ASSERT_H
#define HANGAR_ASSERT_H

namespace Hangar {
	void Assert(bool expression, const std::string& msg, const char* file, int64_t line);
}

#ifdef HANGAR_ENABLE_ASSERT
#define HANGAR_ASSERT(expression, msg) Hangar::Assert(expression, msg, __FILE__, __LINE__);
#else
#define HANGAR_ASSERT(...)
#endif

#endif