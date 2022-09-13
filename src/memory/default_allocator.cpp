#include "precompiled.h"
#include "default_allocator.h"

namespace {
	DefaultAllocator g_allocator;
}

DefaultAllocator* DefaultAllocator::get() {
	return &g_allocator;
}

block_t DefaultAllocator::allocate(size_t size) {
	usage += size;
	allocs++;
	size_t* memory = (size_t*)SDL_malloc(size + sizeof(size_t));
	memory[0] = size;
	return (block_t)&memory[1];
}

void DefaultAllocator::deallocate(block_t block) {
	if (!block)
		return;
	size_t* block_64 = (size_t*)block;
	size_t memory_size = block_64[-1];
	allocs--;
	usage -= memory_size;
	SDL_free(&block_64[-1]);
}

block_t DefaultAllocator::reallocate(block_t block, size_t new_size) {
	block_t new_block = allocate(new_size);
	memcpy(new_block, block, new_size);
	deallocate(block);
	return new_block;
}

block_t HangarC::default_allocate(size_t size) {
	return DefaultAllocator::get()->allocate(size);
}

void HangarC::default_deallocate(block_t block) {
	DefaultAllocator::get()->deallocate(block);
}

block_t operator new(size_t size) noexcept {
	return HangarC::default_allocate(size);
}

void operator delete(block_t block) noexcept {
	HangarC::default_deallocate(block);
}