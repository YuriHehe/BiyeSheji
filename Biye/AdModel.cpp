#include "AdModel.h"

namespace data {
void AdModel::ParseFromString(const std::string & str)
{
	// TODO ½âÎö
}
int AdModel::get_items(const std::string & field, std::vector<int64_t>& ret_value) const
{
	auto it = target_items.find(field);
	if (it == target_items.end()) {
		return RET_ERROR;
	}
	ret_value = it->second;
	return RET_SUCCESS;
}
}