#include "BitmapMgr.h"
#include "log.h"

namespace bitmap {
BitmapPtr BitmapMgr::allocate()
{
	return std::shared_ptr<Bitmap>(malloc(), [=](BitmapP p) {
		free(p);
	});
}

void BitmapMgr::enlarge(size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		BitmapP p = new Bitmap();
		buffers_.Push(p);
	}
}

void BitmapMgr::free(BitmapP p)
{
	p->Clear();
	buffers_.Push(p);
}

BitmapP BitmapMgr::malloc()
{
	BitmapP p = buffers_.Pop();
	if (p == nullptr) {
		TRACE_LOG("bitmap enlarge 1024");
		enlarge(1024);
		p = buffers_.Pop();
	}
	while (p == nullptr) {
		ERROR_LOG("bitmap malloc error");
		TRACE_LOG("bitmap enlarge 1024");
		enlarge(1024);
		p = buffers_.Pop();
	}
	return p;
}
} // namespace bitmap