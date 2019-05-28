#include "offline_rand_model.h"
#include "log.h"

namespace offline {
void rand_model()
{
	// 100w
	const int MAXADS = 1e6;
	std::ofstream of;
	of.open("rand_model.model", 'w');
	double p = 0;
	for (int i = 0; i < MAXADS; ++i) {
		of << i + 1 << " ";
		rand_field(of, "age", 20, 10);
		rand_field(of, "gender", 2, 1);
		of << std::endl;
		double p2 = i * 1.0 / MAXADS;
		if (p2 - p > 0.01) {
			INFO_LOG("Progress" + std::to_string(p2) + "%");
			p = p2;
		}
	}
	INFO_LOG("Success");
}

void rand_field(std::ofstream& os, std::string field, int64_t range, int64_t num) {
	if (num == 0) {
		return;
	}
	os << field << "[";
	for (int i = 0; i < num; ++i) {
		if (i != 0) os << ",";
		os << (rand() * rand() + rand()) % range;
	}
	os << "] ";
}
}