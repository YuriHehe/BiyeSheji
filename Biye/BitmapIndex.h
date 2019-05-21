#pragma once

#include "BitmapMgr.h"
#include "AdModel.h"
#include "usercontext.h"
#define BITMAP_MAGIC_ALL -1
namespace bitmap {
typedef std::unordered_map<int64_t, BitmapPtr> Index;
typedef std::unordered_map<std::string, Index> IndexData;
class BitmapIndex {
public:
	BitmapIndex();

	int Search(const Service::Req& req, Service::Rsp& rsp) const;

	int add_to_index(const std::unordered_map<int64_t, data::AdModel> & model);

	int gen_result(BitmapPtr include_ads, std::vector<int64_t> res_aids) const;

	bool is_allow_field(const std::string &field) const;

private:
	IndexData index_;

	std::unordered_set<std::string> allow_field_;

	std::vector<int64_t> index_2_adid_;

	std::unordered_map<int64_t, size_t> adid_2_index_;

	size_t adcount_;
};
}