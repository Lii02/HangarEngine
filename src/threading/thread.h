#ifndef THREAD_H
#define THREAD_H

typedef int(*ThreadFunction)(void*);

enum {
	THREAD_SUCCESS,
	THREAD_FAILURE = -1,
};

class Thread {
private:
	SDL_Thread* thread;
	ThreadFunction func;
	void* argument;
	int return_code;
	bool joined;
public:
	Thread(ThreadFunction _func = nullptr, void* _argument = nullptr);
	~Thread();

	void set_params(ThreadFunction _func, void* _argument);
	void start_thread();
	void join();
	void detach();
	static uint32_t get_id();

	HANGAR_FORCE_INLINE int get_return_code() const { return return_code; }
};

#endif