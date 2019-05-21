#include "iotask.h"


namespace Task {
int Task::IoTask::realrun()
{
	mock_listen();

	return RET_SUCCESS;
}

void Task::IoTask::mock_listen()
{
	
}
}

