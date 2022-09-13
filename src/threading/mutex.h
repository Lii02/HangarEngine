#ifndef MUTEX_H
#define MUTEX_H

class Mutex {
private:
	SDL_mutex* mutex;
	bool locked;
public:
	Mutex();
	~Mutex();

	void lock();
	void unlock();

	HANGAR_FORCE_INLINE bool is_locked() const { return locked; }
};

class AutomaticMutex {
private:
	Mutex* mutex;
public:
	AutomaticMutex(Mutex* _mutex);
	~AutomaticMutex();

	HANGAR_FORCE_INLINE bool is_locked() const { return mutex->is_locked(); }
};

#endif