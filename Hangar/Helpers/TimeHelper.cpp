#include "Precompiled.h"
#include "TimeHelper.h"

namespace TimeHelper {
	uint64_t UnixTimestamp() {
		return time(NULL);
	}

	std::string TimeString24H() {
		char buffer[100];
		auto t = std::time(nullptr);
		std::strftime(buffer, sizeof(buffer), "%T", std::localtime(&t));
		return std::string(buffer);
	}
}