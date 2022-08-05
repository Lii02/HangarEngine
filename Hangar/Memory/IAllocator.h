#ifndef IALLOCATOR_H
#define IALLOCATOR_H

class IAllocator {
protected:
	size_t usage; // Optional depending on allocator type
public:
	IAllocator() : usage(0) { }
	IAllocator(const IAllocator&) = delete;
	virtual ~IAllocator() { }

	virtual void* Allocate(size_t size) = 0;
	virtual void Deallocate(void* block) = 0;

	inline size_t GetUsage() const { return usage; }
};

#endif