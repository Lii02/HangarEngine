#ifndef STRINGITERATOR_H
#define STRINGITERATOR_H

class StringIterator {
private:
	std::string* str;
	uint32_t index;
public:
	StringIterator(std::string& _str);
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