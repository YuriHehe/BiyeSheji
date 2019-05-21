#include "BitmapIndexMgr.h"
#include "log.h"

namespace bitmap {
void bitmap::BitmapIndexMgr::init()
{
}

int BitmapIndexMgr::build(const std::unordered_map<int64_t, data::AdModel> & models)
{
	BitmapIndexPtr new_data = BitmapIndexPtr(new BitmapIndex());
	// build
	new_data->add_to_index(models);

	// Ìæ»»¾ÉÊý¾Ý
	{
		std::lock_guard<std::mutex> lock(mtx_);
		std::swap(new_data, index_);
	}
	return RET_SUCCESS;
}

int BitmapIndexMgr::Search(const Service::Req & req, Service::Rsp & rsp)
{
	BitmapIndexPtr index;
	{
		std::lock_guard<std::mutex> lock(mtx_);
		index = index_;
	}
	if (index == nullptr) {
		ERROR_LOG("bitmap index not build");
		return RET_ERROR;
	}
	int ret2 = index->SearchStupid(req, rsp);
	int ret = index->Search(req, rsp);
	return ret;
}

}