#ifndef ATOMICS_H
#define ATOMICS_H
#include "precompiled.h"
#include "Mutex.h"
#include "memory/default_allocator.h"

typedef void(*AtomicFreeFunction)(void* block);

template <typename T, AtomicFreeFunction F = HangarC::default_deallocate>
class Atomic {
private:
	T* value;
	mutable Mutex mutex;
public:
	Atomic(T* _value = nullptr) {
		value = _value;
	}

	~Atomic() {
		F(value);
	}

	void load(T* _value) {
		mutex.lock();
		if (_value != nullptr) {
			F(value);
		}
		value = _value;
		mutex.unlock();
	}

	const T& get() const {
		AutomaticMutex auto_mutex = AutomaticMutex(&mutex);
		return *value;
	}
};

typedef Atomic<bool> AtomicBool;
typedef Atomic<float> AtomicF32;
typedef Atomic<double> AtomicF64;

#endif