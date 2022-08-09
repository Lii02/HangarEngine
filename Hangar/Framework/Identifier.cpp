#include "Precompiled.h"
#include "Identifier.h"
#include "../Helpers/TimeHelper.h"

HangarIdentifier::HangarIdentifier() {
	this->str = new char[HANGAR_IDENTIFIER_LENGTH + 1];
	memset(str, 0, HANGAR_IDENTIFIER_LENGTH);
	Generate();
}

HangarIdentifier::~HangarIdentifier() {
}

const char* HangarIdentifier::GetString() {
	return str;
}

HangarIdentifier::operator const char* () {
	return GetString();
}

HangarIdentifier::operator char* () {
	return const_cast<char*>(str);
}

HangarIdentifier::operator std::string() {
	return std::string(str);
}

void HangarIdentifier::Generate() {
	uint64_t timestamp = TimeHelper::UnixTimestamp();
	itoa(timestamp, str, 16);
	itoa(0x4C69, str + 8, 16);
	for (int i = 12; i < HANGAR_IDENTIFIER_LENGTH; i++) {
		uint8_t random = rand() % 0x0F;
		itoa(random, str + i, 16);
	}
}