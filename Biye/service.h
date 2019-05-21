#pragma once

#include "predefine.h"
#include "usercontext.h"

namespace Service {
class AdService {
public:
	void run();

private:
	void run_io_thread();
};
}
