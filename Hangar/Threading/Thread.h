#ifndef THREAD_H
#define THREAD_H

class Thread {
private:
	std::thread* thread;
public:
	Thread();
	virtual ~Thread();

	void Run();
	void Join();
	void Detach();
	bool Joinable() const;
	void* GetHandle();

	virtual void Function() = 0;

	static uint32_t GetThreadCount();
};

#endif