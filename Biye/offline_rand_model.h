#pragma once

#include "predefine.h"

namespace offline {
void rand_model();

void rand_field(std::ofstream& os, std::string field, int64_t range, int64_t num);
}