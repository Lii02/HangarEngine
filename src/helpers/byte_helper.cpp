#include "precompiled.h"
#include "byte_helper.h"

namespace ByteHelper {
	uint16_t swap_16(uint16_t val) {
		return _byteswap_ushort(val);
	}

	uint32_t swap_32(uint32_t val) {
		return _byteswap_ulong(val);
	}

	uint64_t swap_64(uint64_t val) {
		return _byteswap_uint64(val);
	}
}