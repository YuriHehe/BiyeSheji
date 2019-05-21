#pragma once

#include "predefine.h"
#include "usercontext.h"
#include "RingBuffer.h"

// 用于模拟线上请求

namespace mock {

class MockMgr {
public:
	static MockMgr* instance() {
		static MockMgr instance;
		return &instance;
	}

	~MockMgr() {
	}

	void PushReq(Service::REQ* req);

	Service::REQ* PopReq();
private:
	std::mutex mtx_msg_;

private:
	// 等待队列
	ringbuffer::RingBuffer<Service::REQ> wait_list_;

	std::mutex mutex_;

	// 队列为空
	std::atomic<bool> cond_empty_;
};
}