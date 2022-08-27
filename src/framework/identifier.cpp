#include "precompiled.h"
#include "identifier.h"
#include "helpers/time_helper.h"
#include "string/astring.h"

Identifier::Identifier() {
	str = new char[HANGAR_IDENTIFIER_LENGTH + 1];
	memset(str, 0, HANGAR_IDENTIFIER_LENGTH);
}

Identifier::~Identifier() {
	delete[] str;
}

Identifier::Identifier(const Identifier& right) {
	str = new char[HANGAR_IDENTIFIER_LENGTH + 1];
	strcpy(str, right.str);
}

Identifier Identifier::operator=(const Identifier& right) {
	Identifier id;
	strcpy(str, right.str);
	return id;
}

const char* Identifier::get_string() {
	return str;
}

const char* Identifier::get_string() const {
	return str;
}

void Identifier::generate() {
	uint64_t timestamp = TimeHelper::get_unix_timestamp();
	itoa(timestamp, str, 16);
	itoa(0x4C69, str + 8, 16);
	for (int i = 12; i < HANGAR_IDENTIFIER_LENGTH; i++) {
		uint8_t random = rand() % 0x0F;
		itoa(random, str + i, 16);
	}
}

Identifier Identifier::new_identifier() {
	Identifier id;
	id.generate();
	return id;
}

bool operator<(const Identifier& left, const Identifier& right) {
	return AString(left.get_string()).hash() < AString(right.get_string()).hash();
}

bool operator>(const Identifier& left, const Identifier& right) {
	return AString(left.get_string()).hash() > AString(right.get_string()).hash();
}