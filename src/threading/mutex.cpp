#include "precompiled.h"
#include "mutex.h"

Mutex::Mutex() {
	is_locked = false;
}

void Mutex::lock() {
	m.lock();
	is_locked = true;
}

void Mutex::unlock() {
	m.unlock();
	is_locked = false;
}

void* Mutex::get_handle() {
	return m.native_handle();
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