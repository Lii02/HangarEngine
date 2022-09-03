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
	MutexLock lock(&mutex);
	printf("[Hangar | Message | %s]: %s\n", StringFuncs::get_time_string_24h().ptr(), msg.ptr());
}

void Logger::error(const AString& msg) {
	MutexLock lock(&mutex);
	printf("[Hangar | Error | %s]: %s\n", StringFuncs::get_time_string_24h().ptr(), msg.ptr());
}

void Logger::warning(const AString& msg) {
	MutexLock lock(&mutex);
	printf("[Hangar | Warning | %s]: %s\n", StringFuncs::get_time_string_24h().ptr(), msg.ptr());
}

void Logger::confirmation(const AString& msg) {
	MutexLock lock(&mutex);
	printf("[Hangar | Confirm | %s]: %s\n", StringFuncs::get_time_string_24h().ptr(), msg.ptr());
}

void Logger::assertion(const AString& msg, const char* file, int64_t line) {
	MutexLock lock(&mutex);
	printf("[Hangar | Assert | %s:%d | %s]: %s\n", file, line, StringFuncs::get_time_string_24h().ptr(), msg.ptr());
}