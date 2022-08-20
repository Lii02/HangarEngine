#include "Precompiled.h"
#include "Identifier.h"
#include <Helpers/TimeHelper.h>

Identifier::Identifier() {
	this->str = new char[HANGAR_IDENTIFIER_LENGTH + 1];
	memset(str, 0, HANGAR_IDENTIFIER_LENGTH);
}

Identifier::~Identifier() {
	delete[] str;
}

Identifier::Identifier(const Identifier& right) {
	this->str = new char[HANGAR_IDENTIFIER_LENGTH + 1];
	strcpy(str, right.str);
}

Identifier Identifier::operator=(const Identifier& right) {
	Identifier id;
	strcpy(str, right.str);
	return id;
}

const char* Identifier::GetString() {
	return str;
}

const char* Identifier::GetString() const {
	return str;
}

void Identifier::Generate() {
	uint64_t timestamp = TimeHelper::UnixTimestamp();
	itoa(timestamp, str, 16);
	itoa(0x4C69, str + 8, 16);
	for (int i = 12; i < HANGAR_IDENTIFIER_LENGTH; i++) {
		uint8_t random = rand() % 0x0F;
		itoa(random, str + i, 16);
	}
}

Identifier Identifier::New() {
	Identifier id;
	id.Generate();
	return id;
}

bool operator<(const Identifier& left, const Identifier& right) {
	return std::hash<std::string>{}(left.GetString()) < std::hash<std::string>{}(right.GetString());
}

bool operator>(const Identifier& left, const Identifier& right) {
	return std::hash<std::string>{}(left.GetString()) > std::hash<std::string>{}(right.GetString());
}