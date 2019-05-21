#include "offline_rand_model.h"

namespace offline {
void rand_model()
{
	// 100w���
	const int MAXADS = 1e6;
	std::ofstream of;
	of.open("rand_model.model", 'w');
	for (int i = 0; i < MAXADS; ++i) {
		of << i + 1 << " ";
		rand_field(of, "age", 20, 10);
		rand_field(of, "gender", 2, 1);
	}
}

void rand_field(std::ofstream& os, std::string field, int64_t range, int64_t num) {
	if (num == 0) {
		return;
	}
	os << field << "[";
	for (int i = 0; i < num; ++i) {
		os << (rand() * rand() + rand()) % range;
	}
	os << "] ";
}
}