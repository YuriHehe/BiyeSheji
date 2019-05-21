#include "conf.h"

namespace conf{
ConfMgr::ConfMgr()
{
}
void conf::ConfMgr::init(const std::string &file_name)
{
	std::ifstream is(file_name.c_str());
	std::string line;
	while (std::getline(is, line)) {
		std::stringstream ss(line);
		std::string name;
		std::string value;
		ss >> name >> value;
		kv_[name] = value;
	}
}
std::string ConfMgr::get(const std::string &name)
{
	return get(name, "");
}
int64_t ConfMgr::get_int(const std::string &name, int64_t default_value)
{
	std::string str = get(name);
	int ret = default_value;
	try {
		ret = std::stoll(str);
	} catch(...) {
	}
	return ret;
}
int64_t ConfMgr::get_int(const std::string &name)
{
	return get_int(name, 0);
}
std::string ConfMgr::get(const std::string & name, const std::string default_value)
{
	if (kv_.find(name) == kv_.end()) {
		return default_value;
	}
	return kv_[name];
}
} // namespace conf
