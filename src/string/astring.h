#ifndef ASTRING_H
#define ASTRING_H
#include "containers/stretch.h"

class String;

class AStringIterator {
	friend class String;
private:
	char* current;
public:
	AStringIterator(char* _current);

	AStringIterator operator++();
	AStringIterator& operator++(int);
	AStringIterator operator--();
	AStringIterator& operator--(int);
	bool operator==(const AStringIterator& right);
	bool operator!=(const AStringIterator& right);
	char operator*();
};

class AString {
	friend class StringIterator;
private:
	Stretch<char> stretch;
public:
	AString();
	AString(size_t _start_capacity, char c);
	AString(const char* _str);
	AString(const AString& _astring_copy);

	static AString int_to_string(int number);
	static AString float_to_string(float number);
	char* ptr();
	const char* ptr() const;
	size_t get_length() const;
	size_t get_capacity() const;
	void resize(size_t new_capacity);
	void append(char c);
	char pop();
	uint64_t hash() const;
	void clear();
	void copy(const AString& astring_copy);
	char& first();
	char& last();
	char& at(size_t i);
	AString substring(size_t offset, size_t count);
	AStringIterator begin();
	AStringIterator end();
	bool operator==(const AString& str);
	bool operator!=(const AString& str);
	AString operator=(const AString& astring_copy);
	char& operator[](size_t i);
	const char& operator[](size_t i) const;
};

AString operator+(const AString& left, const AString& right);

#endif