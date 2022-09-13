#include "precompiled.h"
#include "thread.h"

Thread::Thread(ThreadFunction _func, void* _argument) {
	set_params(_func, _argument);
	joined = false;
}

Thread::~Thread() {
}

void Thread::set_params(ThreadFunction _func, void* _argument) {
	func = _func;
	argument = _argument;
}

void Thread::start_thread() {
	thread = SDL_CreateThread(func, "HangarThread", argument);
}

void Thread::join() {
	SDL_WaitThread(thread, &return_code);
	joined = true;
}

void Thread::detach() {
	SDL_DetachThread(thread);
}

uint32_t Thread::get_id() {
	return SDL_ThreadID();
}