#ifndef LOGGER_H
#define LOGGER_H

namespace Logger {
	void Message(const std::string& msg);
	void Error(const std::string& msg);
	void Warning(const std::string& msg);
	void Confirmation(const std::string& msg);
}

#endif