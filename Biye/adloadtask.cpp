#include "adloadtask.h"
#include "taskmgr.h"
#include "log.h"
#include "AdModel.h"
#include "BitmapIndexMgr.h"
#include "util.h"

namespace Task {
int AdloadTask::realrun()
{
	while (!is_stoping()) {
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
	std::unordered_map<int64_t, data::AdModel> models;

	std::ifstream ifile;
	ifile.open("local_model.model");
	std::string line;
	while (std::getline(ifile, line)) {
		std::stringstream ss(line);
		int64_t aid;
		ss >> aid;
		models[aid].set_aid(aid);
		std::string field_item;
		while (ss >> field_item) {
			// split item
			std::vector<std::string> res;
			util::string_split_to_vector(field_item, '[', res);
			if (res.size() != 2) {
				ERROR_LOG("ad model field item parse ERROR!");
				continue;
			}
			std::string field = res[0];
			util::string_split_to_vector(res[1], ']', res);
			if (res.size() != 1) {
				ERROR_LOG("ad model field item parse ERROR!");
				continue;
			}
			std::string s_items = res[0];
			std::vector<int64_t> values;
			util::string_split_to_int_vector(s_items, ',', values);
			if (values.size() != 0) {
				models[aid].set_items(field, values);
			}
		}
	}

	bitmap::BitmapIndexMgr::instance()->build(models);

	INFO_LOG("end data reload");
}
}
