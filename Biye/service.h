#pragma once

#include "predefine.h"
#include "usercontext.h"
#include "conf.h"
#include "wokertask.h"

namespace Service {
class AdService {
public:
	AdService() : worker_num(conf::ConfMgr::instance()->get_int("worker_num", 10)) {
		worker.resize(worker_num);
	}

	void run() {
		// 启动worker
		for (int i = 0; i < worker_num; ++i) {
			worker[i].run();
		}
		// 启动adload
		adload.run();
	}
private:
	int worker_num;
	std::vector<Task::WorkerTask> worker;
	Task::AdloadTask adload;
};
}
