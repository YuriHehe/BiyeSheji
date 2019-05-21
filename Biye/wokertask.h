#pragma once

#include "task.h"

namespace Task {
class WorkerTask : public TaskBase {
public:
	WorkerTask() : TaskBase() {};
protected:
	virtual int realrun() override;
private:
	void mock_listen();
};
}