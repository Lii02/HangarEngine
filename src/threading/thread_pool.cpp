#include "precompiled.h"
#include "thread_pool.h"

namespace {
	ThreadPool* g_ThreadPool;
}

void ThreadPool::initialize(size_t _thread_pool_size) {
	g_ThreadPool = new ThreadPool(_thread_pool_size);
}

void ThreadPool::deinitialize() {
	delete g_ThreadPool;
}

ThreadPool*& ThreadPool::get() {
	return g_ThreadPool;
}

ThreadPool::ThreadPool(size_t thread_pool_size) {
	pool_size = thread_pool_size;
	start();
}

ThreadPool::~ThreadPool() {
	stop();
}

void ThreadPool::start() {
	done = false;
	for (size_t i = 0; i < pool_size; i++) {
		workers.emplace_back(new std::thread([&]() {
			while (true) {
				Pair<ThreadFunction, void*> job;
				{
					std::unique_lock<std::mutex> lock(mut);

					cond.wait(lock, [=] { return done || !jobs.empty(); });

					if (done && jobs.empty())
						break;

					job = jobs.front();
					jobs.pop();
				}
				job.first(job.second);
			}
		}));
	}
}

void ThreadPool::stop() {
	done = true;

	cond.notify_all();
	for (std::thread*& worker : workers) {
		worker->join();
		delete worker;
	}
	workers.clear();
}

void ThreadPool::add_job(ThreadFunction job, void* args) {
	std::unique_lock<std::mutex> lock(mut);
	jobs.emplace(job, args);
}