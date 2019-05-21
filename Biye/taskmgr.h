#pragma once

#include "predefine.h"
#include "threadpool.h"
#include "conf.h"

namespace Task {
class TaskMgr {
public:
	static TaskMgr* instance() {
		static TaskMgr instance_;
		return &instance_;
	}

	TaskMgr() : worker_pool_(conf::ConfMgr::instance()->get_int("thread_pool_num", 20)) {}

	template<class F, class... Args>
	auto run(F&& f, Args&&... args)
		->std::future<typename std::result_of<F(Args...)>::type>;
private:
	thread::ThreadPool worker_pool_;
};

template<class F, class ...Args>
inline auto TaskMgr::run(F && f, Args && ...args) -> std::future<typename std::result_of<F(Args ...)>::type>
{
	return worker_pool_.enqueue(f, args...);
}
}