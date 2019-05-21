#include "TestService.h"
#include "Mock.h"
#include "log.h"

int mock::TestService::realrun()
{
	// ������
	while (!is_stoping()) {
		Service::REQ req;
		req.req_.req_id = rand() * rand() % int64_t(1e9 + 7);
		auto& tar = req.req_.user_context.target_items;
		{
			// ��������
			tar["age"].push_back(rand()%10);
			tar["gender"].push_back(rand()%2);
		}
		mock::MockMgr::instance()->PushReq(&req);
		// �ȴ�ִ�����
		req.mtx_.lock();
		std::stringstream ss;
		for (auto aid : req.rsp_.res_aids) {
			ss << aid << " ";
		}
		std::string s;
		ss >> s;
		INFO_LOG("Complete age " + std::to_string(tar["age"][0]) + " gender " + std::to_string(tar["gender"][0]) + " ads: " + s);
	}
	return 0;
}
