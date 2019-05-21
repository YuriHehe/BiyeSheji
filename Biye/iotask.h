#pragma once

#include "predefine.h"
#include "task.h"

namespace Task {
class IoTask : TaskBase {
public:
	IoTask() : stop_sign_(false) {};

	~IoTask() {
		stop();
		handler_.wait();
	}

protected:
	virtual int realrun() override;

private:
	void mock_listen();

private:
	std::atomic<bool> stop_sign_;

	std::future<int> handler_;
};
}