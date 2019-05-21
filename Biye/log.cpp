#include "log.h"
#include "conf.h"

namespace Log {
LogMgr::LogMgr()
{
	// 默认info
	log_level_ = conf::ConfMgr::instance()->get("log_level", "info");
}
void LogMgr::Trace(std::string msg, std::string function, int line, std::string file)
{
	if (log_level_ != "trace") {
		return;
	}
	link_msg(msg, function, line, file, "TRACE");
	push_log(msg);
}
void LogMgr::Info(std::string msg, std::string function, int line, std::string file)
{
	if (log_level_ != "trace" && 
		log_level_ != "info") {
		return;
	}
	link_msg(msg, function, line, file, "INFO");
	push_log(msg);
}
void LogMgr::Warn(std::string msg, std::string function, int line, std::string file)
{
	if (log_level_ != "trace"&&
		log_level_ != "info" &&
		log_level_ != "warn") {
		return;
	}
	link_msg(msg, function, line, file, "WARN");
	push_log(msg);
}
void LogMgr::Error(std::string msg, std::string function, int line, std::string file)
{
	link_msg(msg, function, line, file, "ERROR");
	push_log(msg);
}
void LogMgr::link_msg(std::string & msg, std::string function, int line, std::string file, std::string level)
{
	msg = "[" + level + "][" + file + ":" + std::to_string(line) + "][" + function + "]" + msg;
}
void LogMgr::push_log(std::string msg)
{
	std::lock_guard<std::mutex> lock(mtx_);

	logs_.push_back(msg);

	out_log();
}

void LogMgr::out_log()
{
	// TODO 现在这样非常不好,应该单独开一个线程来做这个事情
	if (logs_.size() > 0) {
		for (auto tmp : logs_) {
			std::cout << tmp << std::endl;
		}
	}
	logs_.clear();
}
} // namespace Log
