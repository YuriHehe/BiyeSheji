#pragma once

#include "BitmapPredefine.h"
#include "Bitmap.h"
#include "RingBuffer.h"

namespace bitmap {

typedef Bitmap* BitmapP;
typedef std::shared_ptr<Bitmap> BitmapPtr;

class BitmapMgr {
public:
	static BitmapMgr* instance() {
		static BitmapMgr instance_;
		return &instance_;
	}

	static BitmapMgr* instance_thread() {
		// ����ÿ�������������µ�bitmap,���Լ���������
		static thread_local BitmapMgr instance_;
		return &instance_;
	}

	BitmapPtr allocate();

private:
	void enlarge(size_t size);
	void free(BitmapP);
	BitmapP malloc();

private:
	ringbuffer::RingBuffer<Bitmap> buffers_;
	std::mutex mtx_;
};
} // namespace bitmap