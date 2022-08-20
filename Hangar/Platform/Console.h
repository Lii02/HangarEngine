#ifndef CONSOLE_H
#define CONSOLE_H

enum ConsoleTextColor : uint8_t {
	DEFAULT,
	YELLOW,
	RED,
	MAGENTA,
	GREEN
};

class Console {
private:
	class Impl;
	Impl* consoleImpl;
public:
	static Console*& Get();
	static void Initialize();
	static void DeInitialize();

	Console();
	~Console();

	void ResetColors();
	void SetTextColor(ConsoleTextColor color);
};

#endif