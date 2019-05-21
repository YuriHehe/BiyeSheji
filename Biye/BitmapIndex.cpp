#include "BitmapIndex.h"
#include "log.h"

namespace bitmap {
BitmapIndex::BitmapIndex()
{
}
int BitmapIndex::Search(const Service::Req& req, Service::Rsp& rsp) const
{
	auto include_ads = BitmapMgr::instance_thread()->allocate();
	include_ads->Flip();

	for (const auto& field : allow_field_) {
		auto exclude_ads = BitmapMgr::instance_thread()->allocate();
		const auto& index_field = index_.find(field);
		if (index_field == index_.end()) {
			ERROR_LOG("field not found");
			continue;
		}
		const auto& field_all = index_field->second.find(BITMAP_MAGIC_ALL);
		if (field_all == index_field->second.end()) {
			ERROR_LOG("all not found");
			continue;
		}
		exclude_ads->Union(*field_all->second);
		const auto& items = req.user_context.target_items;
		auto itr = items.find(field);
		if (itr != items.end()) {
			for (auto value : itr->second) {
				const auto field_value = index_field->second.find(value);
				if (field_value == index_field->second.end()) {
					INFO_LOG("field value not found");
					continue;
				}
				exclude_ads->Exclude(*field_value->second);
			}
		}
		include_ads->Exclude(*exclude_ads);
	}

	return RET_SUCCESS;
}
int BitmapIndex::add_to_index(const std::unordered_map<int64_t, data::AdModel> & models)
{
	for (const auto& p2 : models) {
		const auto model = p2.second;
		size_t index = adcount_++;
		int64_t aid = model.aid();
		adid_2_index_[aid] = index;
		index_2_adid_[index] = aid;
		for (const auto& field : allow_field_) {
			std::vector<int64_t> value;
			int ret = model.get_items(field, value);
			if (ret != RET_SUCCESS) {
				continue;
			}
			// add
			for (auto v : value) {
				index_[field][v]->Set(index, 1); 
			}
			index_[field][BITMAP_MAGIC_ALL]->Set(index, 1);
		}
	}

	return RET_SUCCESS;
}
int BitmapIndex::gen_result(BitmapPtr include_ads, std::vector<int64_t> res_aids) const
{
	std::vector<int> indexs;
	include_ads->get_set_list(indexs);
	res_aids.reserve(indexs.size());
	for (auto index : indexs) {
		res_aids.push_back(index_2_adid_[index]);
	}
	return RET_SUCCESS;
}
bool BitmapIndex::is_allow_field(const std::string & field) const
{
	return allow_field_.find(field) == allow_field_.end();
}
}
