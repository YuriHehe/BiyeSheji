// Biye.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "conf.h"
#include "log.h"
#include "test.h"
#include "TestService.h"
#include "service.h"
#include "offline_rand_model.h"

int main()
{
	conf::ConfMgr::instance()->init("conf.conf");
	std::string type = conf::ConfMgr::instance()->get("run_type", "test");
	if (type == "test") {
		test::Test();
	}
	else if (type == "rand_model") {
		offline::rand_model();
	}
	else {
		// test server
		mock::TestService test_service;
		// main server
		Service::AdService service;
		// run
		service.run();
		while (!bitmap::BitmapIndexMgr::instance()->ready()) {}
		test_service.run();
		int a;
		while (true) {
			std::cin >> a;
			if (a == 0) break;
		}
	}
	int a;
	std::cin >> a;
    return 0;
}

