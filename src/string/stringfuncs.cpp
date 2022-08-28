#include "precompiled.h"
#include "stringfuncs.h"

AString StringFuncs::get_time_string_24h() {
	char buffer[100];
	auto t = time(nullptr);
	strftime(buffer, sizeof(buffer), "%T", localtime(&t));
	return AString(buffer);
}