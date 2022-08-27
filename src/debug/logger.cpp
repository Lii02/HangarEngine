#include "Precompiled.h"
#include "Logger.h"
#include "platform/console.h"
#include "helpers/time_helper.h"
#include "threading/mutex.h"

namespace Logger {
	Mutex g_logger_mutex;

	void initialize() {
		Console::initialize();
	}

	void deinitialize() {
		Console::deinitialize();
	}

	void message(const AString& msg) {
		g_logger_mutex.lock();
		Console::get()->set_text_color(ConsoleTextColor::DEFAULT);
		printf("[Hangar | Message | %s]: %s\n", TimeHelper::get_time_string_24().ptr(), msg.ptr());
		Console::get()->reset_colors();
		g_logger_mutex.unlock();
	}
	
	void error(const AString& msg) {
		g_logger_mutex.lock();
		Console::get()->set_text_color(ConsoleTextColor::RED);
		printf("[Hangar | Error | %s]: %s\n", TimeHelper::get_time_string_24().ptr(), msg.ptr());
		Console::get()->reset_colors();
		g_logger_mutex.unlock();
	}
	
	void warning(const AString& msg) {
		g_logger_mutex.lock();
		Console::get()->set_text_color(ConsoleTextColor::YELLOW);
		printf("[Hangar | Warning | %s]: %s\n", TimeHelper::get_time_string_24().ptr(), msg.ptr());
		Console::get()->reset_colors();
		g_logger_mutex.unlock();
	}

	void confirmation(const AString& msg) {
		g_logger_mutex.lock();
		Console::get()->set_text_color(ConsoleTextColor::GREEN);
		printf("[Hangar | Confirmation | %s]: %s\n", TimeHelper::get_time_string_24().ptr(), msg.ptr());
		Console::get()->reset_colors();
		g_logger_mutex.unlock();
	}
	
	void assertion(const AString& msg, const char* file, int64_t line) {
		g_logger_mutex.lock();
		Console::get()->set_text_color(ConsoleTextColor::MAGENTA);
		printf("[Hangar | Assert fail | %s, %d | %s]: %s\n", file, line, TimeHelper::get_time_string_24().ptr(), msg.ptr());
		Console::get()->reset_colors();
		g_logger_mutex.unlock();
	}
}