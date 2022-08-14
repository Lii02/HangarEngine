#ifndef STRINGITERATOR_H
#define STRINGITERATOR_H

class StringIterator {
private:
	std::string* str;
	uint32_t index;
public:
	StringIterator(std::string& str);
	StringIterator(const StringIterator&) = delete;

	uint32_t GetIndex() const;
	void ResetIndex();
	bool IsEnd() const;
	char Advance();
	char Peek() const;
	bool IsDigit(char c) const;
	bool IsAlpha(char c) const;
	bool IsAlphaNum(char c) const;
	char PeekNext() const;
};

#endif