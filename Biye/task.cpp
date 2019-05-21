#include "task.h"
#include "taskmgr.h"

namespace Task {
void TaskBase::run()
{
	stop_sign_ = true;
	handler_.wait();
	stop_sign_ = false;

	handler_ = TaskMgr::instance()->run([=]() {
		return realrun();
	});
}

void TaskBase::stop()
{
	stop_sign_ = false;
}
TaskBase::~TaskBase()
{
	stop();
	handler_.wait();
}
}
