#pragma once

#include "predefine.h"
#include "usercontext.h"
#include "RingBuffer.h"

// ����ģ����������

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
	// �ȴ�����
	ringbuffer::RingBuffer<Service::REQ> wait_list_;

	std::mutex mutex_;

	// ����Ϊ��
	std::atomic<bool> cond_empty_;
};
}