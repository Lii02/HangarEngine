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
		printf("[Hangar | Message | %s]: %s\n", TimeHelper::get_time_string_24().c_str(), msg.c_str());
		Console::get()->reset_colors();
	}
	
	void error(const std::string& msg) {
		std::lock_guard<std::mutex> lck(g_LoggerMutex);
		Console::get()->set_text_color(ConsoleTextColor::RED);
		printf("[Hangar | Error | %s]: %s\n", TimeHelper::get_time_string_24().c_str(), msg.c_str());
		Console::get()->reset_colors();
	}
	
	void warning(const std::string& msg) {
		std::lock_guard<std::mutex> lck(g_LoggerMutex);
		Console::get()->set_text_color(ConsoleTextColor::YELLOW);
		printf("[Hangar | Warning | %s]: %s\n", TimeHelper::get_time_string_24().c_str(), msg.c_str());
		Console::get()->reset_colors();
	}

	void confirmation(const std::string& msg) {
		std::lock_guard<std::mutex> lck(g_LoggerMutex);
		Console::get()->set_text_color(ConsoleTextColor::GREEN);
		printf("[Hangar | Confirmation | %s]: %s\n", TimeHelper::get_time_string_24().c_str(), msg.c_str());
		Console::get()->reset_colors();
	}
	
	void assertion(const std::string& msg, const char* file, int64_t line) {
		std::lock_guard<std::mutex> lck(g_LoggerMutex);
		Console::get()->set_text_color(ConsoleTextColor::MAGENTA);
		printf("[Hangar | Assert fail | %s, %d | %s]: %s\n", file, line, TimeHelper::get_time_string_24().c_str(), msg.c_str());
		Console::get()->reset_colors();
	}
}