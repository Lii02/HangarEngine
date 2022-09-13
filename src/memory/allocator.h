#ifndef IALLOCATOR_H
#define IALLOCATOR_H

typedef void* block_t;

class IAllocator {
protected:
	size_t usage, allocs;
	
	void _reset_usage() {
		usage = 0;
		allocs = 0;
	}
public:
	IAllocator() {
		_reset_usage();
	}
	virtual ~IAllocator() { }

	virtual block_t allocate(size_t size) = 0;
	virtual void deallocate(block_t block) = 0;
	virtual block_t reallocate(block_t block, size_t new_size) = 0;
	template <typename T>
	T* allocate_template() {
		return (T*)allocate(sizeof(T));
	}

	template <typename T>
	T* reallocate_template(T* block, size_t new_size) {
		return (T*)reallocate(block, sizeof(T) * new_size);
	}

	HANGAR_FORCE_INLINE size_t get_usage() const { return usage; }
	HANGAR_FORCE_INLINE size_t get_allocs() const { return allocs; }
};

#endif