#include "TestService.h"
#include "Mock.h"
#include "log.h"
#include "util.h"

int mock::TestService::realrun()
{
	INFO_LOG("run test service");
	while (!is_stoping()) {
		Service::REQ req;
		req.req_.req_id = rand() * rand() % int64_t(1e9 + 7);
		auto& tar = req.req_.user_context.target_items;
		{
			tar["age"].push_back(rand()%10);
			tar["gender"].push_back(rand()%2);
		}
		mock::MockMgr::instance()->PushReq(&req);
		while (!req.ready_) {}
		INFO_LOG("Complete age " + util::int_vector_to_string(tar["age"]) + " gender " + util::int_vector_to_string(tar["gender"]) + " ads: " + util::int_vector_to_string(req.rsp_.res_aids));
		//std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return 0;
}
