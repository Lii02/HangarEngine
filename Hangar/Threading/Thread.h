#ifndef THREAD_H
#define THREAD_H

#undef Yield

class Thread {
private:
	std::thread* thread;
	std::mutex mut;
public:
	Thread();
	virtual ~Thread();

	void Run();
	void Join();
	void Detach();
	bool Joinable() const;
	void* GetHandle();
	std::mutex& GetMutex();

	virtual void Function() = 0;

	static void Sleep(int milliseconds);
	static void Yield();
	static uint32_t GetThreadCount();
};

#endif