#include "Precompiled.h"
#include "ByteHelper.h"

namespace ByteHelper {
	uint16_t Swap16(uint16_t val) {
		return _byteswap_ushort(val);
	}

	uint32_t Swap32(uint32_t val) {
		return _byteswap_ulong(val);
	}

	uint64_t Swap64(uint64_t val) {
		return _byteswap_uint64(val);
	}
}