#ifndef MUTEX_H
#define MUTEX_H
#include <SDL2/SDL_mutex.h>

class Mutex {
private:
	SDL_mutex* m;
	bool is_locked;
public:
	Mutex();
	~Mutex();

	void lock();
	void unlock();
	bool get_is_locked() const;
};

class MutexLock {
private:
	Mutex* mutex;
public:
	MutexLock(Mutex* _mutex);
	~MutexLock();
	MutexLock(const MutexLock&) = delete;
};

#endif