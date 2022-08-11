#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#define HANGAR_IDENTIFIER_LENGTH 16

class Identifier {
public:
	Identifier();
	~Identifier();
	Identifier(const Identifier&) = delete;

	const char* GetString();
	operator const char*();
	operator char* ();
	operator std::string();
	void Generate();
private:
	char* str;
};

#endif