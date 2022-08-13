#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#define HANGAR_IDENTIFIER_LENGTH 16

class Identifier {
public:
	Identifier();
	~Identifier();
	Identifier(const Identifier& right);
	
	const char* GetString();
	const char* GetString() const;
	void Generate();
private:
	char* str;
};

bool operator<(const Identifier& left, const Identifier& right);
bool operator>(const Identifier& left, const Identifier& right);

#endif