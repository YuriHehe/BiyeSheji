#pragma once

#include "predefine.h"

namespace rit {
// ���ڹ�����õ�field����
class RitFieldMgr {
public:
	static RitFieldMgr* instance() {
		static RitFieldMgr instance_;
		return &instance_;
	}

	bool is_allow_field(const std::string& field) {
		// TODO ��ʱֱ�ӷ���true
		return true;
	}
private:
};
}