#include "Precompiled.h"
#include "Logger.h"
#include "../Platform/Console.h"
#include "../Helpers/TimeHelper.h"

namespace Logger {
	void Message(const std::string& msg) {
		Console::Get().SetTextColor(ConsoleTextColor::DEFAULT);
		std::cout << "[Hangar | Message | " << TimeHelper::TimeString24H() << "]: " << msg << std::endl;
		Console::Get().ResetColors();
	}
	
	void Error(const std::string& msg) {
		Console::Get().SetTextColor(ConsoleTextColor::RED);
		std::cout << "[Hangar | Error | " << TimeHelper::TimeString24H() << "]: " << msg << std::endl;
		Console::Get().ResetColors();
	}
	
	void Warning(const std::string& msg) {
		Console::Get().SetTextColor(ConsoleTextColor::YELLOW);
		std::cout << "[Hangar | Warning | " << TimeHelper::TimeString24H() << "]: " << msg << std::endl;
		Console::Get().ResetColors();
	}

	void Confirmation(const std::string& msg) {
		Console::Get().SetTextColor(ConsoleTextColor::GREEN);
		std::cout << "[Hangar | Confirmation | " << TimeHelper::TimeString24H() << "]: " << msg << std::endl;
		Console::Get().ResetColors();
	}
	
	void Assertion(const std::string& msg, const char* file, int64_t line) {
		Console::Get().SetTextColor(ConsoleTextColor::MAGENTA);
		std::cout << "[Hangar | Assert fail | " << file << ", " << line << "]: " << msg << std::endl;
		Console::Get().ResetColors();
	}
}