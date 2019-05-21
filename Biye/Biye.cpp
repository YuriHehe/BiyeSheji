// Biye.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "conf.h"
#include "log.h"
#include "test.h"

int main()
{
	conf::ConfMgr::instance()->init("conf.conf");
	std::string type = conf::ConfMgr::instance()->get("run_type", "test");
	if (type == "test") {
		test::Test();
	}
	else {
		// run server
	}
	int a;
	std::cin >> a;
    return 0;
}

