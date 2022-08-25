#include "precompiled.h"
#include "memory.h"

namespace {
	static DefaultMemoryAllocator g_allocator;
}

DefaultMemoryAllocator& DefaultMemoryAllocator::get() {
	return g_allocator;
}

DefaultMemoryAllocator::DefaultMemoryAllocator()
	: Allocator() {
}

void* DefaultMemoryAllocator::allocate(size_t size) {
	usage += size;
	allocs++;
	size_t* memory = (size_t*)malloc(size + sizeof(size_t));
	memory[0] = size;
	return (void*)&memory[1];
}

void DefaultMemoryAllocator::deallocate(void* memory) {
	if (!memory)
		return;
	size_t* block_64 = (size_t*)memory;
	size_t memory_size = block_64[-1];
	allocs--;
	usage -= memory_size;
	free(&block_64[-1]);
}

void* DefaultMemoryAllocator::reallocate(void* memory, size_t old_size, size_t new_size) {
	void* new_memory = allocate(new_size);
	memcpy(new_memory, memory, new_size);
	deallocate(memory);
	return new_memory;
}

void* operator new(size_t size) noexcept {
	return DefaultMemoryAllocator::get().allocate(size);
}

void operator delete(void* memory) noexcept {
	DefaultMemoryAllocator::get().deallocate(memory);
}