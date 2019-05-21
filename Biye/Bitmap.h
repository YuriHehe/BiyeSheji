#pragma once

#include "BitmapPredefine.h"

namespace bitmap {
class Bitmap {
friend class Bitmap;
public:
	Bitmap();

	void Clear();

	void Union(const Bitmap& bitmap);

	void Intersect(const Bitmap & bitmap);

	void Copy(const Bitmap & bitmap);

	void Exclude(const Bitmap & bitmap);

	uint32_t nbit();

	void get_set_list(std::vector<int>& list);

	void Set(size_t index, bool bit);

	void Flip();

	void Dump();
private:
	std::bitset<BITMAP_SIZE> bits_;
};
} // namespace bitmap