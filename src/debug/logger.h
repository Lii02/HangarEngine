#ifndef LOGGER_H
#define LOGGER_H
#include "string/astring.h"

namespace Logger {
	void initialize();
	void deinitialize();
	void message(const AString& msg);
	void error(const AString& msg);
	void warning(const AString& msg);
	void confirmation(const AString& msg);
	void assertion(const AString& msg, const char* file, int64_t line);
}

#endif