#ifndef STRINGITERATOR_H
#define STRINGITERATOR_H
#include "string/astring.h"

class StringIterator {
private:
	AString* str;
	uint32_t index;
public:
	StringIterator(AString& _str);
	StringIterator(const StringIterator&) = delete;

	uint32_t get_index() const;
	void reset_index();
	bool is_end() const;
	char advance();
	char peek() const;
	bool is_digit(char c) const;
	bool is_alpha(char c) const;
	bool is_alpha_num(char c) const;
	char peek_next() const;
};

#endif