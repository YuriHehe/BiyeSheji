#pragma once

#include "predefine.h"

namespace Service {
class UserContext {
public:
	// 请求带的定向条件
	std::unordered_map<std::string, std::vector<int64_t>> target_items;
};

class Req {
public:
	int64_t req_id;

	UserContext user_context;
};

class Rsp {
	std::vector<int64_t> res_aids;
};

}