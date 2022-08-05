#include "Precompiled.h"
#include "MemoryManager.h"

// TODO: Fix ugly globals
namespace {
	size_t g_memoryUsage = 0; // Memory usage in bytes
	size_t g_memoryAllocs = 0; // Current # of memory blocks in use
}

void* MemoryAllocate(size_t size) {
	size_t* rawBlock = (size_t*)std::malloc(size + sizeof(size_t));
	rawBlock[0] = size;
	g_memoryUsage += size;
	g_memoryAllocs++;
	return (void*)&rawBlock[1];
}

void MemoryFree(void* block) {
	if (!block)
		return;
	size_t* sizeBlock = (size_t*)block;
	size_t blockSize = sizeBlock[-1];
	void* rawBlock = (void*)(&sizeBlock[-1]);
	g_memoryUsage -= blockSize;
	g_memoryAllocs--;
	std::free(rawBlock);
}

size_t MemoryUsage() {
	return g_memoryUsage;
}

size_t MemoryAllocs() {
	return g_memoryAllocs;
}