#pragma once

#include "task.h"

namespace Task {
class WorkerTask : public TaskBase {
public:

protected:
	virtual int realrun() override;
private:
};
}