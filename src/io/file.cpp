#include "precompiled.h"
#include "file.h"
#include "debug/assert.h"
#include "debug/logger.h"
#include "memory/memory.h"

File::File(AString _path, FileMode _mode, AString _filename) {
	path = _path;
	mode = _mode;
	filename = _filename;
	is_open = false;
}

File::~File() {
	if(is_open)
		close();
}

bool File::open() {
	char* mode_string = new char[2];
	memset(mode_string, '\0', 2);
	switch (mode)
	{
	case FileMode::READ:
		mode_string[0] = 'r';
		break;
	case FileMode::WRITE:
		mode_string[0] = 'w';
		break;
	case FileMode::APPEND:
		mode_string[0] = 'a';
		break;
	}

	stream = fopen(path.ptr(), mode_string);
	delete[] mode_string;
	is_open = true;
	return stream != nullptr;
}

void File::close() {
	HANGAR_ASSERT(is_open, "File stream is already closed");
	fclose(stream);
	is_open = false;
}

void File::rewind_ptr() {
	rewind(stream);
}

bool File::reopen() {
	if (is_open) {
		close();
	}
	return open();
}

void File::write_byte(uint8_t b) {
	fwrite((void*)&b, 1, 1, stream);
}

void File::write_string(const char* str) {
	fwrite(str, strlen(str), 1, stream);
}

void File::write_buffer(const void* buffer, size_t length) {
	fwrite(buffer, length, 1, stream);
}

void* File::read_buffer(size_t length) {
	DefaultMemoryAllocator& allocator = DefaultMemoryAllocator::get();
	void* block = allocator.allocate(length);
	fread(block, length, 1, stream);
	return block;
}

AString File::read_string(size_t length) {
	AString str(length + 1, '\0');
	fread((void*)str.ptr(), length, 1, stream);
	return str;
}

size_t File::length() {
	fseek(stream, 0, SEEK_END);
	size_t length = ftell(stream);
	rewind_ptr();
	return length;
}