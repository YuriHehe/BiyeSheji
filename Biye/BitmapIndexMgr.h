#pragma once

#include "BitmapIndex.h"
#include "AdModel.h"
#include "usercontext.h"

namespace bitmap {
typedef std::shared_ptr<BitmapIndex> BitmapIndexPtr;

class BitmapIndexMgr {
public:
	static BitmapIndexMgr* instance() {
		static BitmapIndexMgr instance_;
		return &instance_;
	}

	void init();

	int build(const std::unordered_map<int64_t, data::AdModel> & models);

	// �̰߳�ȫ��search
	int Search(const Service::Req& req, Service::Rsp& rsp);
private:
	// ˫buffer����
	BitmapIndexPtr index_;

	std::mutex mtx_;
};
}