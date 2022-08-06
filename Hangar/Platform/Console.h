#ifndef CONSOLE_H
#define CONSOLE_H

enum ConsoleTextColor : uint8_t {
	DEFAULT,
	YELLOW,
	RED,
	GREEN
};

class Console {
private:
	class Impl;
	Impl* consoleImpl;
public:
	static Console& Get();

	Console();
	~Console();

	void ResetColors();
	void SetTextColor(ConsoleTextColor color);
};

#endif