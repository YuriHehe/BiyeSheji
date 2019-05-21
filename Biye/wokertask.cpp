#include "wokertask.h"
#include "Mock.h"
#include "BitmapIndexMgr.h"
#include "log.h"

namespace Task {
int WorkerTask::realrun()
{
	mock_listen();

	return RET_SUCCESS;
}

void WorkerTask::mock_listen()
{
	while (!is_stoping()) {
		auto req = mock::MockMgr::instance()->PopReq();
		if (req == nullptr) {
			continue;
		}
		// work
		int ret = bitmap::BitmapIndexMgr::instance()->Search(req->req_, req->rsp_);
		if (ret != RET_SUCCESS) {
			ERROR_LOG("Error Search, error code:" + std::to_string(ret));
		}
		req->ready_ = true;
	}
}
}