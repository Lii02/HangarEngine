#include "precompiled.h"
#include "thread.h"

Thread::Thread() {
}

Thread::~Thread() {
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