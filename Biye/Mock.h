#pragma once

#include "predefine.h"
#include "usercontext.h"

// 用于模拟线上请求

namespace mock {
class MockMgr {
public:
	void PushReq(const Service::Req& req, Service::Rsp& rsp);

	std::pair<const Service::Req*, Service::Rsp*> PopReq();

	std::shared_mutex& get_mutex();

public:
	// 用于唤醒io线程用的
	std::shared_mutex mtx_msg_;

private:
	// 等待队列
	std::vector<std::pair<Service::Req*, Service::Rsp*>> wait_list_;

	std::mutex mutex_;

	// 队列为空
	std::atomic<bool> cond_empty_;

};
}