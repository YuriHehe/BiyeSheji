#pragma once
#include "predefine.h"
#include "task.h"

namespace mock {
class TestService : public Task::TaskBase {
protected:
	virtual int realrun();
};
}