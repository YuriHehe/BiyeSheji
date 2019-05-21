#pragma once

#include "predefine.h"

#define TRACE_LOG(msg) Log::LogMgr::instance()->Trace((msg), __FUNCTION__, __LINE__, __FILE__)
#define INFO_LOG(msg) Log::LogMgr::instance()->Info((msg), __FUNCTION__, __LINE__, __FILE__)
#define WARN_LOG(msg) Log::LogMgr::instance()->Warn((msg), __FUNCTION__, __LINE__, __FILE__)
#define ERROR_LOG(msg) Log::LogMgr::instance()->Error((msg), __FUNCTION__, __LINE__, __FILE__)

namespace Log {
class LogMgr {
public:
	static LogMgr* instance() {
		static LogMgr instance_;
		return &instance_;
	}
	LogMgr();
	//~LogMgr();

	void Trace(std::string msg, std::string function, int line, std::string file);
	void Info(std::string msg, std::string function, int line, std::string file);
	void Error(std::string msg, std::string function, int line, std::string file);
	void Warn(std::string msg, std::string function, int line, std::string file);
private:
	void link_msg(std::string& msg, std::string function, int line, std::string file, std::string level);

	void push_log(std::string msg);

	void out_log();

private:
	std::string log_level_;

	// TODO 暂时就弄个全局锁
	std::mutex mtx_;

	std::vector<std::string> logs_;
};
} // namespace log