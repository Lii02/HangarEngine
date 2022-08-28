#include "Precompiled.h"
#include "Logger.h"
#include "platform/console.h"
#include "string/stringfuncs.h"

namespace {
	Logger* g_logger;
}

Logger* Logger::get() {
	return g_logger;
}

void Logger::initialize() {
	g_logger = new Logger;
}

void Logger::deinitialize() {
	delete g_logger;
}

Logger::Logger() {
	Console::initialize();
}

Logger::~Logger() {
	Console::deinitialize();
}

void Logger::message(const AString& msg) {
	mutex.lock();
	Console::get()->set_text_color(ConsoleTextColor::DEFAULT);
	printf("[Hangar | Message | %s]: %s\n", StringFuncs::get_time_string_24h().ptr(), msg.ptr());
	Console::get()->reset_colors();
	mutex.unlock();
}

void Logger::error(const AString& msg) {
	mutex.lock();
	Console::get()->set_text_color(ConsoleTextColor::RED);
	printf("[Hangar | Error | %s]: %s\n", StringFuncs::get_time_string_24h().ptr(), msg.ptr());
	Console::get()->reset_colors();
	mutex.unlock();
}

void Logger::warning(const AString& msg) {
	mutex.lock();
	Console::get()->set_text_color(ConsoleTextColor::YELLOW);
	printf("[Hangar | Warning | %s]: %s\n", StringFuncs::get_time_string_24h().ptr(), msg.ptr());
	Console::get()->reset_colors();
	mutex.unlock();
}

void Logger::confirmation(const AString& msg) {
	mutex.lock();
	Console::get()->set_text_color(ConsoleTextColor::GREEN);
	printf("[Hangar | Confirmation | %s]: %s\n", StringFuncs::get_time_string_24h().ptr(), msg.ptr());
	Console::get()->reset_colors();
	mutex.unlock();
}

void Logger::assertion(const AString& msg, const char* file, int64_t line) {
	mutex.lock();
	Console::get()->set_text_color(ConsoleTextColor::MAGENTA);
	printf("[Hangar | Assert fail | %s, %d | %s]: %s\n", file, line, StringFuncs::get_time_string_24h().ptr(), msg.ptr());
	Console::get()->reset_colors();
	mutex.unlock();
}