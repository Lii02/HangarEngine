#ifndef FILE_H
#define FILE_H

enum class FileMode {
	READ,
	WRITE,
	APPEND
};

class File {
private:
	std::string path;
	FileMode mode;
	FILE* stream;
	bool isOpen;
public:
	File(std::string path, FileMode mode);
	~File();

	bool Open();
	void Close();
	void Rewind();
	void WriteByte(uint8_t b);
	void WriteString(const char* str);
	void WriteBuffer(const void* buffer, size_t length);
	uint8_t ReadByte();
	void* ReadBuffer(size_t length);
	std::string ReadString(size_t length);
	size_t Length();

	inline bool IsOpen() const { return isOpen; }
};

#endif