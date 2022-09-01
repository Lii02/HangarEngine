#include "precompiled.h"
#include "mutex.h"

Mutex::Mutex() {
	is_locked = false;
	m = SDL_CreateMutex();
}

Mutex::~Mutex() {
	SDL_DestroyMutex(m);
}

void Mutex::lock() {
	SDL_LockMutex(m);
	is_locked = true;
}

void Mutex::unlock() {
	SDL_UnlockMutex(m);
	is_locked = false;
}

bool Mutex::get_is_locked() const {
	return is_locked;
}

MutexLock::MutexLock(Mutex* _mutex) {
	mutex = _mutex;
	mutex->lock();
}

MutexLock::~MutexLock() {
	mutex->unlock();
}