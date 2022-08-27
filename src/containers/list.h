#ifndef LIST_H
#define LIST_H
#include "containers/stretch.h"

template <typename T>
class List {
	friend class Iterator;
public:
	class Iterator {
		friend class List;
	private:
	public:
	};
private:
	Stretch<T> stretch;
public:
	List(size_t start_capacity = 1)
	: stretch(start_capacity) {
	}

	List(const List& list_copy) {
		stretch.copy(list_copy);
	}

	void push(T data) {
		if(get_size() >= get_capacity())
			stretch.double_capacity();
		stretch[stretch.increase_size()] = data;
	}

	void pop() {
		stretch.decrease_size();
	}

	void skip() {
		stretch.increase_size();
	}

	size_t get_size() const {
		return stretch.get_size();
	}

	size_t get_capacity() const {
		return stretch.get_capacity();
	}

	size_t get_allocated() const {
		return stretch.get_allocated();
	}

	List& operator=(const List& list_copy) {
		copy(list_copy);
		return *this;
	}

	T& operator[](size_t index) {
		return stretch[index];
	}

	const T& operator[](size_t index) const {
		return stretch[index];
	}
};

#endif