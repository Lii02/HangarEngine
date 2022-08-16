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
	bool isOpen;
public:
	File(std::string path, FileMode mode, std::string filename);
	~File();
	File(const File&) = delete;

	bool Open();
	void Close();
	void Rewind();
	void WriteByte(uint8_t b);
	void WriteString(const char* str);
	void WriteBuffer(const void* buffer, size_t length);
	void* ReadBuffer(size_t length);
	std::string ReadString(size_t length);
	template <typename T>
	T Read() {
		T val;
		fread((void*)&val, sizeof(T), 1, stream);
		return val;
	}
	size_t Length();

	inline bool IsOpen() const { return isOpen; }
	inline std::string GetPath() const { return path; }
	inline std::string GetFilename() const { return filename; }
};

#endif