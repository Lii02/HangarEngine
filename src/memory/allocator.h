#ifndef ALLOCATOR_H
#define ALLOCATOR_H

class Allocator {
protected:
	size_t usage; // Optional depending on allocator type
public:
	Allocator() : usage(0) { }
	Allocator(const Allocator&) = delete;
	virtual ~Allocator() { }

	virtual void* allocate(size_t size) = 0;
	virtual void deallocate(void* block) = 0;

	inline size_t get_usage() const { return usage; }
};

#endif