#include "precompiled.h"
#include "hashing.h"

uint64_t Hashing::hash_djb2(const uint8_t* buffer, size_t buffer_length) {
	uint64_t hash = 5381;
	for (size_t i = 0; i < buffer_length; i++) {
		hash = ((hash << 5) + hash) + buffer[i];
	}
	return hash;
}