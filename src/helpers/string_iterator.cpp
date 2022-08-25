#include "precompiled.h"
#include "string_iterator.h"

StringIterator::StringIterator(std::string& selected_str) {
	this->str = &selected_str;
	reset_index();
}

uint32_t StringIterator::get_index() const {
	return index;
}

void StringIterator::reset_index() {
	this->index = 0;
}

bool StringIterator::is_end() const {
	return index >= str->length();
}

char StringIterator::advance() {
	return str->at(index++);
}

char StringIterator::peek() const {
	if (is_end()) return '\0';
	return str->at(index);
}

bool StringIterator::is_digit(char c) const {
	return c >= '0' && c <= '9';
}

bool StringIterator::is_alpha(char c) const {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool StringIterator::is_alpha_num(char c) const {
	return is_alpha(c) || is_digit(c);
}

char StringIterator::peek_next() const {
	if (index + 1 >= str->length()) return '\0';
	return str->at(index + 1);
}