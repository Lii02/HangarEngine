#include "precompiled.h"
#include "console.h"

#ifdef HANGAR_WINDOWS
class Console::Impl {
	enum ConsoleColor : uint8_t
	{
		COLOR_BLACK = 0,
		COLOR_DARK_BLUE = FOREGROUND_BLUE,
		COLOR_DARK_GREEN = FOREGROUND_GREEN,
		COLOR_DARK_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		COLOR_DARK_RED = FOREGROUND_RED,
		COLOR_DARK_MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
		COLOR_DARK_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		COLOR_GRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		COLOR_DARK_GRAY = FOREGROUND_INTENSITY,
		COLOR_BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		COLOR_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		COLOR_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		COLOR_RED = FOREGROUND_RED | FOREGROUND_INTENSITY,
		COLOR_MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		COLOR_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		COLOR_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	};

private:
	HANDLE console_handle;
	HWND console_window;
public:
	Impl() {
		console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		console_window = GetConsoleWindow();
		reset_colors();
	}

	inline void reset_colors() {
		set_foreground(ConsoleColor::COLOR_WHITE);
		set_background(ConsoleColor::COLOR_BLACK);
	}

	inline void set_text_color(ConsoleTextColor color) {
		switch (color)
		{
		case YELLOW:
			set_foreground(ConsoleColor::COLOR_YELLOW);
			break;
		case RED:
			set_foreground(ConsoleColor::COLOR_RED);
			break;
		case GREEN:
			set_foreground(ConsoleColor::COLOR_GREEN);
			break;
		case MAGENTA:
			set_foreground(ConsoleColor::COLOR_MAGENTA);
			break;
		case DEFAULT:
		default:
			set_foreground(ConsoleColor::COLOR_WHITE);
			break;
		}
	}

private:
	inline void set_foreground(ConsoleColor c) {
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(console_handle, &info);
		SetConsoleTextAttribute(console_handle, info.wAttributes & 0xF0 | (WORD)c);
	}

	inline void set_background(ConsoleColor c) {
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(console_handle, &info);
		SetConsoleTextAttribute(console_handle, info.wAttributes & 0x0F | (WORD)c << 4);
	}
};
#endif

namespace {
	Console* g_Console;
}

Console*& Console::get() {
	return g_Console;
}

void Console::initialize() {
	g_Console = new Console();
}

void Console::deinitialize() {
	delete g_Console;
}

Console::Console() {
	console_impl = new Console::Impl;
}

Console::~Console() {
	delete console_impl;
}

void Console::reset_colors() {
	console_impl->reset_colors();
}

void Console::set_text_color(ConsoleTextColor color) {
	console_impl->set_text_color(color);
}