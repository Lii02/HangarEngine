#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

void* MemoryAllocate(size_t size);
void MemoryFree(void* block);
size_t MemoryUsage();
size_t MemoryAllocs();

inline void* operator new(size_t size) noexcept {
	return MemoryAllocate(size);
}

inline void operator delete(void* block) noexcept {
	MemoryFree(block);
}

#endif
