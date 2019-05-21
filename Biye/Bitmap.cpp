#include "Bitmap.h"
#include "BitmapMgr.h"
#include "log.h"

namespace bitmap {
Bitmap::Bitmap()
{
}

void Bitmap::Clear()
{
	bits_.reset();
}

void Bitmap::Union(const Bitmap & bitmap)
{
	bits_ |= bitmap.bits_;
}

void Bitmap::Intersect(const Bitmap & bitmap)
{
	bits_ &= bitmap.bits_;
}

void Bitmap::Copy(const Bitmap & bitmap)
{
	bits_ = bitmap.bits_;
}

void Bitmap::Exclude(const Bitmap & bitmap)
{
	auto bmp = BitmapMgr::instance_thread()->allocate();
	bmp->Copy(bitmap);
	bmp->Flip();
	Flip();
	Union(*bmp);
	Flip();
}

uint32_t Bitmap::nbit()
{
	return bits_.count();
}

void Bitmap::get_set_list(std::vector<int>& list)
{
	list.clear();
	for (int i = 0; i < BITMAP_SIZE; ++i) {
		if (bits_[i]) {
			list.push_back(i);
		}
	}
}

void Bitmap::Set(size_t index, bool bit)
{
	if (index >= BITMAP_SIZE) {
		ERROR_LOG("wrong index");
	}
	bits_[index] = bit;
}

void Bitmap::Flip()
{
	bits_.flip();
}

} // namespace bitmap