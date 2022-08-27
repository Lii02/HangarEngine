#ifndef THREAD_H
#define THREAD_H
#include "mutex.h"
#include <thread>

typedef void(*ThreadFunction)(void*);

class Thread {
private:
	Mutex mutex;
	std::thread thread;
	ThreadFunction func;
	void* args;
public:
	Thread() = default;
	Thread(ThreadFunction _func, void* _args);
	Thread(const Thread& thread);
	~Thread();

	Mutex& get_mutex();
	void join();
	void detach();
	void* get_handle();
	void run();

	Thread operator=(const Thread& right);
	static void sleep(int milliseconds);
	static void yield();
	static uint32_t get_thread_count();
};

#endif