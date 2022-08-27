#ifndef THREAD_H
#define THREAD_H

class Thread {
private:
public:
	Thread();
	~Thread();

	static void sleep(int milliseconds);
	static void yield();
	static uint32_t get_thread_count();
};

#endif