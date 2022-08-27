#ifndef FILE_H
#define FILE_H
#include "string/astring.h"

enum class FileMode {
	READ,
	WRITE,
	APPEND
};

class File {
private:
	AString path, filename;
	FileMode mode;
	FILE* stream;
	bool is_open;
public:
	File(AString _path, FileMode _mode, AString _filename);
	~File();
	File(const File&) = delete;

	bool open();
	void close();
	void rewind_ptr();
	bool reopen();
	void write_byte(uint8_t b);
	void write_string(const char* str);
	void write_buffer(const void* buffer, size_t length);
	void* read_buffer(size_t length);
	AString read_string(size_t length);
	template <typename T>
	T read() {
		T val;
		fread((void*)&val, sizeof(T), 1, stream);
		return val;
	}
	size_t length();

	inline bool get_is_open() const { return is_open; }
	inline AString get_path() const { return path; }
	inline AString get_filename() const { return filename; }
};

#endif