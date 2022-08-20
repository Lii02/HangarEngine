#include "Precompiled.h"
#include "Console.h"

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
	HANDLE consoleHandle;
	HWND consoleWindow;
public:
	Impl() {
		this->consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		this->consoleWindow = GetConsoleWindow();
		ResetColors();
	}

	inline void ResetColors() {
		SetForeground(ConsoleColor::COLOR_WHITE);
		SetBackground(ConsoleColor::COLOR_BLACK);
	}

	inline void SetTextColor(ConsoleTextColor color) {
		switch (color)
		{
		case YELLOW:
			SetForeground(ConsoleColor::COLOR_YELLOW);
			break;
		case RED:
			SetForeground(ConsoleColor::COLOR_RED);
			break;
		case GREEN:
			SetForeground(ConsoleColor::COLOR_GREEN);
			break;
		case MAGENTA:
			SetForeground(ConsoleColor::COLOR_MAGENTA);
			break;
		case DEFAULT:
		default:
			SetForeground(ConsoleColor::COLOR_WHITE);
			break;
		}
	}

private:
	inline void SetForeground(ConsoleColor c) {
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(consoleHandle, &info);
		SetConsoleTextAttribute(consoleHandle, info.wAttributes & 0xF0 | (WORD)c);
	}

	inline void SetBackground(ConsoleColor c) {
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(consoleHandle, &info);
		SetConsoleTextAttribute(consoleHandle, info.wAttributes & 0x0F | (WORD)c << 4);
	}
};
#endif

namespace {
	Console* g_Console;
}

Console*& Console::Get() {
	return g_Console;
}

void Console::Initialize() {
	g_Console = new Console();
}

void Console::DeInitialize() {
	delete g_Console;
}

Console::Console() {
	consoleImpl = new Console::Impl;
}

Console::~Console() {
	delete consoleImpl;
}

void Console::ResetColors() {
	consoleImpl->ResetColors();
}

void Console::SetTextColor(ConsoleTextColor color) {
	consoleImpl->SetTextColor(color);
}