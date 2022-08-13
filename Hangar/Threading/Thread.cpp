#include "Precompiled.h"
#include "Thread.h"

Thread::Thread() {
	this->thread = nullptr;
}

Thread::~Thread() {
	if (thread != nullptr)
		delete thread;
}

void Thread::Run() {
	if(thread != nullptr)
		this->thread = new std::thread(std::bind(&Thread::Function, this));
}

void Thread::Join() {
	thread->join();
	thread = nullptr;
}

void Thread::Detach() {
	thread->detach();
}

bool Thread::Joinable() const {
	return thread->joinable();
}

void* Thread::GetHandle() {
	return thread->native_handle();
}

uint32_t Thread::GetThreadCount() {
	return std::thread::hardware_concurrency();
}