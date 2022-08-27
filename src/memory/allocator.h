#ifndef ALLOCATOR_H
#define ALLOCATOR_H

struct Allocator {
protected:
	size_t usage, allocs;
public:
	Allocator() {
		usage = 0;
		allocs = 0;
	}
	virtual ~Allocator() { }

	virtual void* allocate(size_t size) = 0;
	virtual void deallocate(void* memory) = 0;
	virtual void* reallocate(void* memory, size_t old_size, size_t new_size) = 0;
	size_t get_usage() const { return usage; }
	size_t get_allocs() const { return allocs; }

	template <typename T>
	T* allocate_template() {
		return (T*)allocate(sizeof(T));
	}

	template <typename T>
	T* reallocate_template(T* memory, size_t old_size, size_t new_size) {
		return (T*)reallocate(memory, old_size * sizeof(T), new_size * sizeof(T));
	}
};

#endif