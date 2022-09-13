#include "precompiled.h"
#include "mutex.h"

Mutex::Mutex() {
	mutex = SDL_CreateMutex();
	locked = false;
}

Mutex::~Mutex() {
	SDL_DestroyMutex(mutex);
}

void Mutex::lock() {
	SDL_LockMutex(mutex);
	locked = true;
}

void Mutex::unlock() {
	SDL_UnlockMutex(mutex);
	locked = false;
}

AutomaticMutex::AutomaticMutex(Mutex* _mutex) {
	mutex = _mutex;
	mutex->lock();
}

AutomaticMutex::~AutomaticMutex() {
	mutex->unlock();
}