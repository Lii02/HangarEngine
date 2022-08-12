#include "Precompiled.h"
#include "File.h"
#include "../Memory/MemoryManager.h"
#include "../Debug/Assert.h"

File::File(std::string path, FileMode mode, std::string filename) {
	this->path = path;
	this->filename = filename;
	this->mode = mode;
	this->isOpen = false;
}

File::~File() {
	if(isOpen)
		Close();
}

bool File::Open() {
	char* modeString = new char[2];
	memset(modeString, '\0', 2);
	switch (mode)
	{
	case FileMode::READ:
		modeString[0] = 'r';
		break;
	case FileMode::WRITE:
		modeString[0] = 'w';
		break;
	case FileMode::APPEND:
		modeString[0] = 'a';
		break;
	}

	stream = fopen(path.c_str(), modeString);
	delete[] modeString;
	this->isOpen = true;
	return stream != nullptr;
}

void File::Close() {
	HANGAR_ASSERT(isOpen, "File stream is already closed");
	fclose(stream);
	this->isOpen = false;
}

void File::Rewind() {
	rewind(stream);
}

void File::WriteByte(uint8_t b) {
	fwrite((void*)&b, 1, 1, stream);
}

void File::WriteString(const char* str) {
	fwrite(str, strlen(str), 1, stream);
}

void File::WriteBuffer(const void* buffer, size_t length) {
	fwrite(buffer, length, 1, stream);
}

uint8_t File::ReadByte() {
	uint8_t b;
	fread((void*)&b, 1, 1, stream);
	return b;
}

void* File::ReadBuffer(size_t length) {
	void* block = MemoryAllocate(length);
	fread(block, length, 1, stream);
	return block;
}

std::string File::ReadString(size_t length) {
	std::string str(length + 1, '\0');
	fread((void*)str.data(), length, 1, stream);
	return str;
}

size_t File::Length() {
	fseek(stream, 0, SEEK_END);
	size_t length = ftell(stream);
	Rewind();
	return length;
}