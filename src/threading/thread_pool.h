#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "containers/list.h"

typedef std::function<void()> ThreadFunction;

class ThreadPool {
private:
	size_t pool_size;
	std::atomic_bool done;
	std::condition_variable cond;
	List<std::thread*> workers;
	std::queue<ThreadFunction> jobs;
	std::mutex mut;
public:
	static void initialize(size_t _thread_pool_size = 2);
	static void deinitialize();
	static ThreadPool*& get();

	ThreadPool(size_t thread_pool_size = 1);
	~ThreadPool();

	void start();
	void stop();
	void add_job(ThreadFunction job);
};

#endif