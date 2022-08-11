#include "Precompiled.h"
#include "StringIterator.h"

StringIterator::StringIterator(std::string& str) {
	this->str = &str;
	ResetIndex();
}

uint32_t StringIterator::GetIndex() const {
	return index;
}

void StringIterator::ResetIndex() {
	this->index = 0;
}

bool StringIterator::IsEnd() const {
	return index >= str->length();
}

char StringIterator::Advance() {
	return str->at(index++);
}

char StringIterator::Peek() const {
	if (IsEnd()) return '\0';
	return str->at(index);
}

bool StringIterator::IsDigit(char c) const {
	return c >= '0' && c <= '9';
}

bool StringIterator::IsAlpha(char c) const {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool StringIterator::IsAlphaNum(char c) const {
	return IsAlpha(c) || IsDigit(c);
}

char StringIterator::PeekNext() const {
	if (index + 1 >= str->length()) return '\0';
	return str->at(index + 1);
}