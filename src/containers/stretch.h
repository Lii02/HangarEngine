#ifndef STRETCH_H
#define STRETCH_H

template <typename T>
class Stretch {
private:
	T* buffer;
	size_t size, capacity;
public:
	~Stretch() {
		free_data();
	}

	void free_data() {
		if (buffer)
			delete[] data;
		data = nullptr;
		size = 0;
		capacity = 0;
	}

	void resize(size_t new_size) {
	}

	size_t get_size() const {
		return size;
	}

	size_t get_capacity() const {
		return capacity;
	}
};

#endif