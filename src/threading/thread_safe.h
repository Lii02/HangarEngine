#ifndef THREAD_SAFE_H
#define THREAD_SAFE_H
#include "threading/mutex.h"

template <class T>
class ThreadSafe {
private:
	T* object;
	Mutex mutex;
public:
	ThreadSafe(T* _object) {
		object = _object;
	}

	~ThreadSafe() {
		delete object;
	}

	void load(T* _object) {
		if (object) {
			mutex.lock();
			delete object;
			object = _object;
			mutex.unlock();
		}
	}

	T* get() {
		MutexLock lock = MutexLock(&mutex);
		return object;
	}
};

#endif