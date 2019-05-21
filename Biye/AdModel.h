#pragma once

#include"predefine.h"

namespace data {
class AdModel {
public:
	void ParseFromString(const std::string &str);

	int get_items(const std::string &field, std::vector<int64_t> &ret_value) const;

	void set_items(const std::string &field, std::vector<int64_t> value) {
		target_items[field] = value;
	}

	void set_aid(int64_t id) {
		ad_id = id;
	}
public:
	int64_t aid() const {
		return ad_id;
	}

private:
	std::unordered_map<std::string, std::vector<int64_t>> target_items;

	int64_t ad_id;
};
}