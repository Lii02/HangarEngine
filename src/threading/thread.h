#ifndef THREAD_H
#define THREAD_H

class Thread {
private:
	std::thread* thread;
	std::mutex mut;
public:
	Thread();
	virtual ~Thread();

	void run();
	void join();
	void detach();
	bool joinable() const;
	void* get_handle();
	std::mutex& get_mutex();

	virtual void function() = 0;

	static void sleep(int milliseconds);
	static void yield();
	static uint32_t get_thread_count();
};

#endif