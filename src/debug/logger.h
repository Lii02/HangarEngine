#ifndef LOGGER_H
#define LOGGER_H

namespace Logger {
	void initialize();
	void deinitialize();
	void message(const std::string& msg);
	void error(const std::string& msg);
	void warning(const std::string& msg);
	void confirmation(const std::string& msg);
	void assertion(const std::string& msg, const char* file, int64_t line);
}

#endif