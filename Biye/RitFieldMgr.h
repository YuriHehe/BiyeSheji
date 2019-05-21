#pragma once

#include "predefine.h"

namespace rit {
// 用于管理可用的field集合
class RitFieldMgr {
public:
	static RitFieldMgr* instance() {
		static RitFieldMgr instance_;
		return &instance_;
	}

	bool is_allow_field(const std::string& field) {
		// TODO 暂时直接返回true
		return true;
	}
private:
};
}