#ifndef HANGAR_MEMORY_H
#define HANGAR_MEMORY_H
#include "allocator.h"

class DefaultMemoryAllocator : public Allocator {
public:
	static DefaultMemoryAllocator& get();

	DefaultMemoryAllocator();

	virtual void* allocate(size_t size) override;
	virtual void deallocate(void* memory) override;
	virtual void* reallocate(void* memory, size_t old_size, size_t new_size) override;
};

void* operator new(size_t size) noexcept;
void operator delete(void* memory) noexcept;

#endif