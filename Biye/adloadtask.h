#pragma once

#include "predefine.h"
#include "task.h"

namespace Task {
class AdloadTask : public TaskBase {
public:
	static AdloadTask* instance() {
		static AdloadTask instance_;
		return &instance_;
	}

protected:
	virtual int realrun() override;

private:
	void reload();

private:
	std::atomic<bool> stop_sign_;

	std::future<int> handler_;
};
}