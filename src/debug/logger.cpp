#include "Precompiled.h"
#include "Logger.h"
#include "platform/console.h"
#include "helpers/time_helper.h"

namespace Logger {
	std::mutex g_LoggerMutex;

	void initialize() {
		Console::initialize();
	}

	void deinitialize() {
		Console::deinitialize();
	}

	void message(const std::string& msg) {
		std::lock_guard<std::mutex> lck(g_LoggerMutex);
		Console::get()->set_text_color(ConsoleTextColor::DEFAULT);
		std::cout << "[Hangar | Message | " << TimeHelper::get_time_string_24() << "]: " << msg << std::endl;
		Console::get()->reset_colors();
	}
	
	void error(const std::string& msg) {
		std::lock_guard<std::mutex> lck(g_LoggerMutex);
		Console::get()->set_text_color(ConsoleTextColor::RED);
		std::cout << "[Hangar | Error | " << TimeHelper::get_time_string_24() << "]: " << msg << std::endl;
		Console::get()->reset_colors();
	}
	
	void warning(const std::string& msg) {
		std::lock_guard<std::mutex> lck(g_LoggerMutex);
		Console::get()->set_text_color(ConsoleTextColor::YELLOW);
		std::cout << "[Hangar | Warning | " << TimeHelper::get_time_string_24() << "]: " << msg << std::endl;
		Console::get()->reset_colors();
	}

	void confirmation(const std::string& msg) {
		std::lock_guard<std::mutex> lck(g_LoggerMutex);
		Console::get()->set_text_color(ConsoleTextColor::GREEN);
		std::cout << "[Hangar | Confirmation | " << TimeHelper::get_time_string_24() << "]: " << msg << std::endl;
		Console::get()->reset_colors();
	}
	
	void assertion(const std::string& msg, const char* file, int64_t line) {
		std::lock_guard<std::mutex> lck(g_LoggerMutex);
		Console::get()->set_text_color(ConsoleTextColor::MAGENTA);
		std::cout << "[Hangar | Assert fail | " << file << ", " << line << "]: " << msg << std::endl;
		Console::get()->reset_colors();
	}
}