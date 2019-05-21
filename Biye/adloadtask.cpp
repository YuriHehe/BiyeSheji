#include "adloadtask.h"
#include "taskmgr.h"
#include "log.h"
#include "AdModel.h"
#include "BitmapIndexMgr.h"

namespace Task {
int AdloadTask::realrun()
{
	while (!stop_sign_) {
		// TODO reload logic
		reload();

		// 5s reload
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return RET_SUCCESS;
}
void AdloadTask::reload()
{
	INFO_LOG("start data reload");
	// �ȴ��ļ���ȡ���
	std::unordered_map<int64_t, data::AdModel> models;

	// ���ع�����ݵ�IndexData
	bitmap::BitmapIndexMgr::instance()->build(models);

	INFO_LOG("end data reload");
}
}
