#pragma once
#include "predefine.h"

namespace conf {
class ConfMgr {
public:
	static ConfMgr* instance() {
		static thread_local ConfMgr conf_mgr;
		return &conf_mgr;
	}
	ConfMgr();

	void init(const std::string& file_name);

	std::string get(const std::string& name);
	std::string get(const std::string& name, const std::string default_value);

private:
	std::unordered_map<std::string, std::string> kv_;
};
}