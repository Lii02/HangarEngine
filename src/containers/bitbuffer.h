#ifndef BITBUFFER_H
#define BITBUFFER_H

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
		// TODO: Check if str is correct size
		for (size_t i = 0; i < strlen(_str); i++) {
			bits[i] = _str[i] == true;
		}
	}

	bool check(unsigned int bit) const {
		// TODO: Check if bit is out of bounds
		return bits[bit];
	}

	void set(unsigned int bit, bool value = true) {
		// TODO: Check if bit is out of bounds
		bits[bit] = value;
	}

	unsigned int get_size() const {
		return size;
	}

	bool& operator[](unsigned int bit) {
		return bits[bit];
	}

	const bool& operator[](unsigned int bit) const {
		return bits[bit];
	}
};

#endif