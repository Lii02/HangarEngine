#ifndef TIMEHELPER_H
#define TIMEHELPER_H
#include "string/astring.h"

namespace TimeHelper {
	uint64_t get_unix_timestamp();
	AString get_time_string_24();
}

#endif