#pragma once

#include "predefine.h"
#include "usercontext.h"

// ����ģ����������

namespace mock {
class MockMgr {
public:
	void PushReq(const Service::Req& req, Service::Rsp& rsp);

	std::pair<const Service::Req*, Service::Rsp*> PopReq();

	std::shared_mutex& get_mutex();

public:
	// ���ڻ���io�߳��õ�
	std::shared_mutex mtx_msg_;

private:
	// �ȴ�����
	std::vector<std::pair<Service::Req*, Service::Rsp*>> wait_list_;

	std::mutex mutex_;

	// ����Ϊ��
	std::atomic<bool> cond_empty_;

};
}