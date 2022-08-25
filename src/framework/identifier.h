#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#define HANGAR_IDENTIFIER_LENGTH 16

class Identifier {
public:
	Identifier();
	~Identifier();
	Identifier(const Identifier& right);
	Identifier operator=(const Identifier& right);
	
	const char* get_string();
	const char* get_string() const;
	void generate();

	static Identifier new_identifier();
private:
	char* str;
};

bool operator<(const Identifier& left, const Identifier& right);
bool operator>(const Identifier& left, const Identifier& right);

#endif