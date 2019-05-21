#pragma once

#include"predefine.h"

namespace data {
class AdModel {
public:
	void ParseFromString(const std::string &str);

	int get_items(const std::string &field, std::vector<int64_t> &ret_value) const;
public:
	int64_t aid() const {
		return ad_id;
	}

private:
	// 定向条件
	std::unordered_map<std::string, std::vector<int64_t>> target_items;

	// 广告属性
	int64_t ad_id;
};
}