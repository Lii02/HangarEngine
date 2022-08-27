#include "precompiled.h"
#include "thread.h"

Thread::Thread(ThreadFunction _func, void* _args) {
	func = _func;
	args = _args;
}

Thread::Thread(const Thread& thread) {
	func = thread.func;
	args = thread.args;
}

Thread::~Thread() {
}

Mutex& Thread::get_mutex() {
	return mutex;
}

void Thread::join() {
	thread.join();
}

void Thread::detach() {
	thread.detach();
}

void* Thread::get_handle() {
	return thread.native_handle();
}

void Thread::run() {
	if(thread.joinable())
		thread.join();
	thread = std::thread(func, args);
}

Thread Thread::operator=(const Thread& right) {
	func = right.func;
	args = right.args;
	return *this;
}

void Thread::sleep(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void Thread::yield() {
	std::this_thread::yield();
}

uint32_t Thread::get_thread_count() {
	return std::thread::hardware_concurrency();
}