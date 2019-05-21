#pragma once

#include "predefine.h"

namespace Service {
class UserContext {
public:
	// ������Ķ�������
	std::unordered_map<std::string, std::vector<int64_t>> target_items;
};

struct Req {
	int64_t req_id;

	UserContext user_context;
};

struct Rsp {
	std::vector<int64_t> res_aids;
};

struct REQ {
	Req req_;
	Rsp rsp_;
	std::mutex mtx_;
};

}