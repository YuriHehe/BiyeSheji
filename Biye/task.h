#pragma once

#include "predefine.h"

namespace Task {
class TaskBase {
public:
	void run();
	void stop();

	TaskBase() : stop_sign_(false) {};
	~TaskBase();

protected:
	virtual int realrun() = 0;

protected:
	std::mutex mtx_;
	std::future<int> handler_;

private:
	std::atomic<bool> stop_sign_;
};
}