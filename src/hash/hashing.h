#ifndef HASHING_H
#define HASHING_H

namespace Hashing {
	uint64_t hash_djb2(const uint8_t* buffer, size_t buffer_length);
}

#endif