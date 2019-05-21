#pragma once

#include "predefine.h"
#include "threadpool.h"

namespace Task {
class TaskMgr {
public:
	static TaskMgr* instance() {
		static TaskMgr instance_;
		return &instance_;
	}

	TaskMgr() : io_pool_(2), worker_pool_(5) {}

	template<class F, class... Args>
	auto run(F&& f, Args&&... args)
		->std::future<typename std::result_of<F(Args...)>::type>;

	template<class F, class... Args>
	auto run_io(F&& f, Args&&... args)
		->std::future<typename std::result_of<F(Args...)>::type>;
private:
	thread::ThreadPool io_pool_;
	thread::ThreadPool worker_pool_;
};

template<class F, class ...Args>
inline auto TaskMgr::run(F && f, Args && ...args) -> std::future<typename std::result_of<F(Args ...)>::type>
{
	return worker_pool_.enqueue(f, args...);
}

template<class F, class ...Args>
inline auto TaskMgr::run_io(F && f, Args && ...args) -> std::future<typename std::result_of<F(Args ...)>::type>
{
	return io_pool_.enqueue(f, args...);
}
}