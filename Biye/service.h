#pragma once

#include "predefine.h"
#include "usercontext.h"
#include "conf.h"
#include "wokertask.h"
#include "adloadtask.h"

namespace Service {
class AdService {
public:
	AdService() : worker_num(conf::ConfMgr::instance()->get_int("worker_num", 10)) {
		for (int i = 0; i < worker_num; ++i) {
			worker.push_back(std::shared_ptr<Task::WorkerTask> (new Task::WorkerTask()));
		}
	}

	void run() {
		// 启动worker
		for (int i = 0; i < worker_num; ++i) {
			worker[i]->run();
		}
		// 启动adload
		adload.run();
	}
private:
	int worker_num;
	std::vector<std::shared_ptr<Task::WorkerTask>> worker;
	Task::AdloadTask adload;
};
}
