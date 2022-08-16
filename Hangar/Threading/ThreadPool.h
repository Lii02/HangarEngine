#ifndef THREADPOOL_H
#define THREADPOOL_H

typedef std::function<void()> ThreadFunction;

class ThreadPool {
private:
	size_t poolSize;
	std::atomic_bool done;
	std::condition_variable cond;
	std::vector<std::thread> workers;
	std::queue<ThreadFunction> jobs;
	std::mutex mut;
public:
	static void Initialize(size_t poolSize = 2);
	static void DeInitialize();
	static ThreadPool*& Get();

	ThreadPool(size_t poolSize = 1);
	~ThreadPool();

	void Start();
	void Stop();
	void AddJob(ThreadFunction job);
};

#endif