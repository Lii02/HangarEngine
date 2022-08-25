#include "Precompiled.h"
#include "Thread.h"

Thread::Thread() {
	thread = nullptr;
}

Thread::~Thread() {
	if (thread != nullptr)
		delete thread;
}

void Thread::run() {
	if(thread != nullptr)
		thread = new std::thread(std::bind(&Thread::function, this));
}

void Thread::join() {
	thread->join();
	thread = nullptr;
}

void Thread::detach() {
	thread->detach();
}

bool Thread::joinable() const {
	return thread->joinable();
}

void* Thread::get_handle() {
	return thread->native_handle();
}

std::mutex& Thread::get_mutex() {
	return mut;
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