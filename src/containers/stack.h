#ifndef STACK_H
#define STACK_H
#include "containers/stack.h"

template <typename T>
class Stack {
private:
	Stretch<T> stretch;
public:
	Stack() {
	}

	Stack(const Stack& _stack_copy) {
		copy(_stack_copy);
	}

	void push(const T& data) {
		if(get_size() >= get_capacity())
			stretch.double_capacity();
		stretch[stretch.increase_size()] = data;
	}

	T& pop() {
		T& value = top();
		stretch.decrease_size();
		return value;
	}

	T* ptr() {
		return stretch.ptr();
	}

	const T* ptr() const {
		return stretch.ptr();
	}

	void copy(const Stack& _stack_copy) {
		stretch.copy(_stack_copy.stretch);
	}

	void clear() {
		stretch.clear();
	}

	T& back() {
		return stretch[0];
	}

	T& top() {
		return stretch[get_size() - 1];
	}

	size_t get_size() const {
		return stretch.get_size();
	}

	size_t get_capacity() const {
		return stretch.get_capacity();
	}

	Stack operator=(const Stack& stack_copy) {
		copy(stack_copy);
		return *this;
	}

	T& operator[](size_t i) {
		return stretch[i];
	}

	const T& operator[](size_t i) const {
		return stretch[i];
	}
};

#endif