#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#define HANGAR_IDENTIFIER_LENGTH 16

class HangarIdentifier {
public:
	HangarIdentifier();
	~HangarIdentifier();
	HangarIdentifier(const HangarIdentifier&) = delete;

	const char* GetString();
	operator const char*();
	operator char* ();
	operator std::string();
	void Generate();
private:
	char* str;
};

#endif