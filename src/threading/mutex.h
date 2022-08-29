#ifndef MUTEX_H
#define MUTEX_H
#include <mutex>

class Mutex {
private:
	std::mutex m;
	bool is_locked;
public:
	Mutex();

	void lock();
	void unlock();
	void* get_handle();
	bool get_is_locked() const;
};

class MutexLock {
private:
	Mutex* mutex;
public:
	MutexLock(Mutex* _mutex);
	~MutexLock();
};

#endif