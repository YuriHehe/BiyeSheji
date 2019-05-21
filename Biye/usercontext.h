#pragma once

#include "predefine.h"

namespace Service {
class UserContext {
public:
	std::unordered_map<std::string, std::vector<int64_t>> target_items;
};

struct Req {
	int64_t req_id;

	UserContext user_context;
};

struct Rsp {
	std::vector<int> res_aids;
};

struct REQ {
	Req req_;
	Rsp rsp_;
	std::atomic<bool> ready_ = false;
};

}