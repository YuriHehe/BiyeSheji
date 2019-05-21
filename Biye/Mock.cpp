#include "Mock.h"

namespace mock {
void MockMgr::PushReq(const Service::Req & req, Service::Rsp & rsp)
{
}

std::pair<const Service::Req*, Service::Rsp*> MockMgr::PopReq()
{
	return std::pair<const Service::Req*, Service::Rsp*>();
}
std::shared_mutex & MockMgr::get_mutex()
{
	return mtx_msg_;
}
}
