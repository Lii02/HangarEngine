#ifndef THREAD_SAFE_H
#define THREAD_SAFE_H
#include "threading/mutex.h"

template <class T>
class ThreadSafe {
private:
	T object;
	mutable Mutex mutex;
public:
	ThreadSafe(T _object) {
		object = _object;
	}

	~ThreadSafe() {
	}

	void load(T _object) {
		mutex.lock();
		object = _object;
		mutex.unlock();
	}

	T& get() {
		MutexLock lock = MutexLock(&mutex);
		return object;
	}

	const T& get() const {
		MutexLock lock = MutexLock(&mutex);
		return object;
	}
};

#endif