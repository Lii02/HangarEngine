#include "precompiled.h"
#include "astring.h"
#include "hash/hashing.h"

AString::AString() {
}

AString::AString(size_t _start_capacity, char c) {
	stretch.set_size(_start_capacity);
	stretch.resize(_start_capacity);
	memset(ptr(), c, _start_capacity);
}

AString::AString(const char* _str) {
	for (size_t i = 0; i < strlen(_str); i++) {
		append(_str[i]);
	}
	append('\0');
}

AString::AString(const AString& _astring_copy) {
	copy(_astring_copy);
}

AString AString::int_to_string(int number) {
	AString str;
	char buffer[10]{ 0 };
	itoa(number, buffer, 10);
	for (size_t i = 0; i < strlen(buffer); i++) {
		str.append(buffer[i]);
	}
	str.append('\0');
	return str;
}

AString AString::float_to_string(float number) {
	AString str;
	char buffer[10]{ 0 };
	sprintf(buffer, "%f", number);
	for (size_t i = 0; i < strlen(buffer); i++) {
		str.append(buffer[i]);
	}
	str.append('\0');
	return str;
}

char* AString::ptr() {
	return stretch.ptr();
}

const char* AString::ptr() const {
	return stretch.ptr();
}

size_t AString::get_length() const {
	return stretch.get_size();
}

size_t AString::get_capacity() const {
	return stretch.get_capacity();
}

void AString::resize(size_t new_capacity) {
	stretch.resize(new_capacity);
}

void AString::append(char c) {
	if(get_length() >= get_capacity())
		stretch.double_capacity();
	stretch[stretch.increase_size()] = c;
}

char AString::pop() {
	char c = stretch[stretch.get_size()];
	stretch.decrease_size();
	return c;
}

uint64_t AString::hash() const {
	return Hashing::hash_djb2((uint8_t*)ptr(), get_length());
}

void AString::clear() {
	stretch.clear();
}

void AString::copy(const AString& astring_copy) {
	stretch.clear();
	for (size_t i = 0; i < astring_copy.get_length(); i++) {
		append(astring_copy[i]);
	}
}

char& AString::first() {
	return stretch[0];
}

char& AString::last() {
	return stretch[get_length()];
}

char& AString::at(size_t i) {
	return stretch[i];
}

AString AString::substring(size_t offset, size_t count) {
	AString str;
	size_t index = 0;
	while (index < count) {
		str.append(at(offset + index));
		index++;
	}
	return str;
}

AStringIterator AString::begin() {
	return AStringIterator(&stretch[0]);
}

AStringIterator AString::end() {
	return AStringIterator(&stretch[get_length()]);
}

bool AString::operator==(const AString& str) {
	return !strcmp(ptr(), str.ptr());
}

bool AString::operator!=(const AString& str) {
	return strcmp(ptr(), str.ptr());
}

AString operator+(const AString& left, const AString& right) {
	AString copy = left;
	copy.pop();
	for(size_t i = 0; i < right.get_length(); i++)
		copy.append(right[i]);
	return copy;
}

AString AString::operator=(const AString& astring_copy) {
	copy(astring_copy);
	return *this;
}

char& AString::operator[](size_t i) {
	return stretch[i];
}

const char& AString::operator[](size_t i) const {
	return stretch[i];
}

AStringIterator::AStringIterator(char* _current) {
	current = _current;
}

AStringIterator AStringIterator::operator++() {
	current++;
	return *this;
}

AStringIterator& AStringIterator::operator++(int) {
	AStringIterator it = *this;
	current++;
	return it;
}

AStringIterator AStringIterator::operator--() {
	current--;
	return *this;
}

AStringIterator& AStringIterator::operator--(int) {
	AStringIterator it = *this;
	current--;
	return it;
}

bool AStringIterator::operator==(const AStringIterator& right) {
	return current == right.current;
}

bool AStringIterator::operator!=(const AStringIterator& right) {
	return current != right.current;
}

char AStringIterator::operator*() {
	return *current;
}