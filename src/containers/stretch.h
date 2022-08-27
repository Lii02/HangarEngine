#ifndef STRETCH_H
#define STRETCH_H
#include "memory/memory.h"
#include "debug/assert.h"

template <typename T>
class Stretch {
private:
	mutable T* buffer;
	size_t size, capacity;
public:
	Stretch(size_t _capacity = 1) {
		HANGAR_ASSERT(_capacity != 0, "Stretch buffer capacity cannot be initialized as 0");
		capacity = _capacity;
		size = 0;
		buffer = new T[capacity];
	}

	Stretch(const Stretch& stretch_copy) {
		copy(stretch_copy);
	}

	~Stretch() {
		free_data();
	}

	void copy(const Stretch& stretch_copy) {
		free_data();
		size = stretch_copy.get_size();
		capacity = stretch_copy.get_capacity();
		buffer = new T[capacity];
		memcpy(buffer, stretch_copy.ptr(), size * sizeof(T));
	}

	size_t get_allocated() const {
		return capacity * sizeof(T);
	}

	T* ptr() {
		return buffer;
	}

	void free_data() {
		if (buffer)
			delete[] buffer;
		buffer = nullptr;
		size = 0;
		capacity = 0;
	}

	void resize(size_t new_capacity) {
		DefaultMemoryAllocator& allocator = DefaultMemoryAllocator::get();
		buffer = allocator.reallocate_template<T>(buffer, capacity, new_capacity);
	}

	void double_capacity() {
		DefaultMemoryAllocator& allocator = DefaultMemoryAllocator::get();
		buffer = allocator.reallocate_template<T>(buffer, capacity, capacity *= 2);
	}

	size_t increase_size() {
		return size++;
	}

	size_t decrease_size() {
		return size--;
	}

	void set_size(size_t new_size) {
		size = new_size;
	}

	size_t get_size() const {
		return size;
	}

	size_t get_capacity() const {
		return capacity;
	}

	bool within_bounds(size_t index) const {
		return index >= 0 && index < size;
	}

	Stretch& operator=(const Stretch& stretch_copy) {
		copy(stretch_copy);
		return *this;
	}

	T& operator[](size_t index) {
		return buffer[index];
	}

	const T& operator[](size_t index) const {
		return buffer[index];
	}
};

#endif