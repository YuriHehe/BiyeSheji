#include "Mock.h"

namespace mock {
void MockMgr::PushReq(Service::REQ* p2)
{
	p2->mtx_.lock();
	std::lock_guard<std::mutex> lock(mtx_msg_);
	wait_list_.Push(p2);
}

Service::REQ* MockMgr::PopReq()
{
	std::lock_guard<std::mutex> lock(mtx_msg_);
	auto ret = wait_list_.Pop();

	return ret;
}
}
