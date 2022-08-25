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
	Impl* console_impl;
public:
	static Console*& get();
	static void initialize();
	static void deinitialize();

	Console();
	~Console();

	void reset_colors();
	void set_text_color(ConsoleTextColor color);
};

#endif