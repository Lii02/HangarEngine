#ifndef DEFAULT_ALLOCATOR_H
#define DEFAULT_ALLOCATOR_H
#include "allocator.h"

class DefaultAllocator : public IAllocator {
public:
	static DefaultAllocator* get();

	virtual block_t allocate(size_t size) override;
	virtual void deallocate(block_t block) override;
	virtual block_t reallocate(block_t block, size_t new_size) override;
};

namespace HangarC {
	extern "C" {
		block_t default_allocate(size_t size);
		void default_deallocate(block_t block);
	}
}

void* operator new(size_t size);
void operator delete(void* block);

#endif