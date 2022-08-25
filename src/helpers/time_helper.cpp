#include "precompiled.h"
#include "time_helper.h"

namespace TimeHelper {
	uint64_t get_unix_timestamp() {
		return time(NULL);
	}

	std::string get_time_string_24() {
		char buffer[100];
		auto t = std::time(nullptr);
		std::strftime(buffer, sizeof(buffer), "%T", std::localtime(&t));
		return std::string(buffer);
	}
}