#include "Precompiled.h"
#include "Logger.h"
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
}

Logger::~Logger() {
}

void Logger::message(const AString& msg) {
	mutex.lock();
	printf("[Hangar | Message | %s]: %s\n", StringFuncs::get_time_string_24h().ptr(), msg.ptr());
	mutex.unlock();
}

void Logger::error(const AString& msg) {
	mutex.lock();
	printf("[Hangar | Error | %s]: %s\n", StringFuncs::get_time_string_24h().ptr(), msg.ptr());
	mutex.unlock();
}

void Logger::warning(const AString& msg) {
	mutex.lock();
	printf("[Hangar | Warning | %s]: %s\n", StringFuncs::get_time_string_24h().ptr(), msg.ptr());
	mutex.unlock();
}

void Logger::confirmation(const AString& msg) {
	mutex.lock();
	printf("[Hangar | Confirmation | %s]: %s\n", StringFuncs::get_time_string_24h().ptr(), msg.ptr());
	mutex.unlock();
}

void Logger::assertion(const AString& msg, const char* file, int64_t line) {
	mutex.lock();
	printf("[Hangar | Assert fail | %s, %d | %s]: %s\n", file, line, StringFuncs::get_time_string_24h().ptr(), msg.ptr());
	mutex.unlock();
}