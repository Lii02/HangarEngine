#ifndef BITBUFFER_H
#define BITBUFFER_H
#include "debug/assert.h"

template <unsigned int B>
class BitBuffer {
private:
	bool bits[B];
	unsigned int size;
public:
	BitBuffer(bool _value = false) {
		size = B;
		memset(bits, _value, size);
	}

	BitBuffer(const char* _str) {
		size = B;
		size_t string_length = strlen(_str) - 1;
		HANGAR_ASSERT(string_length == size, "BitBuffer string length is longer than buffer length");
		for (size_t i = 0; i < string_length; i++) {
			bits[i] = _str[i] == true;
		}
	}

	bool check(unsigned int bit) const {
		HANGAR_ASSERT(bit >= 0 && bit < size, "Bit index is out of bounds");
		return bits[bit];
	}

	void set(unsigned int bit, bool value = true) {
		HANGAR_ASSERT(bit >= 0 && bit < size, "Bit index is out of bounds");
		bits[bit] = value;
	}

	unsigned int get_size() const {
		return size;
	}

	bool within_bounds(size_t index) const {
		return index >= 0 && index < size;
	}

	bool& operator[](unsigned int bit) {
		return bits[bit];
	}

	const bool& operator[](unsigned int bit) const {
		return bits[bit];
	}
};

#endif