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
		T* current;
	public:
		Iterator(T* _current) {
			current = _current;
		}

		Iterator operator++() {
			current++;
			return *this;
		}

		Iterator operator--() {
			current--;
			return *this;
		}

		Iterator& operator++(int) {
			Iterator it = *this;
			current++;
			return it;
		}

		Iterator& operator--(int) {
			Iterator it = *this;
			current--;
			return it;
		}

		Iterator operator+(size_t i) {
			current += i;
			return *this;
		}

		Iterator operator-(size_t i) {
			current -= i;
			return *this;
		}

		T& operator*() {
			return *current;
		}

		bool operator!=(Iterator right) {
			return current != right.current;
		}

		bool operator==(Iterator right) {
			return current != right.current;
		}
	};
private:
	Stretch<T> stretch;
public:
	List(size_t _start_capacity = 1)
		: stretch(_start_capacity) {
	}

	List(const List& _list_copy) {
		copy(_list_copy);
	}

	T* ptr() {
		return stretch.ptr();
	}

	const T* ptr() const {
		return stretch.ptr();
	}

	void copy(const List& new_list) {
		stretch.copy(new_list.stretch);
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

	void clear() {
		stretch.clear();
	}

	void resize(size_t new_capacity) {
		stretch.resize(new_capacity);
	}

	T& front() {
		return stretch[0];
	}

	T& back() {
		return stretch[get_size()];
	}

	Iterator find(Iterator start, Iterator last, const T& value) {
		for (auto it = start; it != last; it++) {
			if(*it == value)
				return it;
		}
		return end();
	}

	Iterator insert(Iterator iterator, T data) {
		if (get_size() == 0 && iterator != end()) {
			push(data);
			iterator = end();
		} else {
			List new_list;
			for (auto it = begin(); it != end(); it++) {
				if (*it == *iterator) {
					new_list.push(data);
					iterator = it;
				}
				new_list.push(*it);
			}
			copy(new_list);
		}
		return iterator;
	}

	Iterator erase(Iterator iterator) {
		if (get_size() == 0) {
			iterator = begin();
		} else {
			List new_list;
			for (auto it = begin(); it != end(); it++) {
				new_list.push(*it);
				if (*it == *iterator) {
					new_list.pop();
					*iterator = *it;
				}
			}
			copy(new_list);
		}
		return iterator;
	}

	Iterator begin() {
		return Iterator(&stretch[0]);
	}

	Iterator end() {
		return Iterator(&stretch[get_size()]);
	}

	Iterator emplace_front(const T& data) {
		auto it = insert(begin(), data);
		return it;
	}

	Iterator emplace_back(const T& data) {
		auto it = insert(end(), data);
		return it;
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