#ifndef FILE_H
#define FILE_H

enum class FileMode {
	READ,
	WRITE,
	APPEND
};

class File {
private:
	std::string path, filename;
	FileMode mode;
	FILE* stream;
	bool is_open;
public:
	File(std::string file_path, FileMode file_mode, std::string file_filename);
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
	std::string read_string(size_t length);
	template <typename T>
	T read() {
		T val;
		fread((void*)&val, sizeof(T), 1, stream);
		return val;
	}
	size_t length();

	inline bool get_is_open() const { return is_open; }
	inline std::string get_path() const { return path; }
	inline std::string get_filename() const { return filename; }
};

#endif