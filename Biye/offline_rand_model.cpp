#include "offline_rand_model.h"

void offline::rand_model()
{
	// 100w¹ã¸æ
	const int MAXADS = 1e6;
	std::ofstream of;
	of.open("rand_model.model", 'w');
	for (int i = 0; i < MAXADS; ++i) {
		of << i + 1 << " ";
		// age
		// gender
	}
}
