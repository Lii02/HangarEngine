#include "Precompiled.h"
#include "ThreadPool.h"

namespace {
	ThreadPool* g_ThreadPool;
}

void ThreadPool::Initialize(size_t poolSize) {
	g_ThreadPool = new ThreadPool(poolSize);
}

void ThreadPool::DeInitialize() {
	delete g_ThreadPool;
}

ThreadPool*& ThreadPool::Get() {
	return g_ThreadPool;
}

ThreadPool::ThreadPool(size_t poolSize) {
	this->poolSize = poolSize;
	Start();
}

ThreadPool::~ThreadPool() {
	Stop();
}

void ThreadPool::Start() {
	this->done = false;
	for (size_t i = 0; i < poolSize; i++) {
		workers.emplace_back([&] {
			while (true) {
				ThreadFunction job;
				{
					std::unique_lock<std::mutex> lock(mut);

					cond.wait(lock, [=] { return done || !jobs.empty(); });

					if (done && jobs.empty())
						break;

					job = jobs.front();
					jobs.pop();
				}
				job();
			}
		});
	}
}

void ThreadPool::Stop() {
	{
		std::unique_lock<std::mutex> lock(mut);
		this->done = true;
	}

	cond.notify_all();
	for (std::thread& worker : workers)
		worker.join();
	workers.clear();
}

void ThreadPool::AddJob(ThreadFunction job) {
	std::unique_lock<std::mutex> lock(mut);
	jobs.emplace([=] { job(); });
}