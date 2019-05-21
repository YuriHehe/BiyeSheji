#pragma once

#include "predefine.h"

namespace ringbuffer {
template <typename T>
class RingBuffer {
public:
	RingBuffer(size_t buffer_size = 1024) {
		buffer_size_ = 0;
		head_ = tail_ = 0;
		buffers_.resize(buffer_size_);
		enlarge(buffer_size);
	}

	~RingBuffer() {
		while (!empty()) {
			T* p = Pop();
			if (p == nullptr) {
				continue;
			}
			delete p;
			p = nullptr;
		}
	}

	void Push(T* item) {
		std::lock_guard<std::mutex> lock(mutex_);
		if (full()) {
			enlarge();
		}

		buffers_[tail_++] = item;
		tail_ %= buffer_size_;
	}

	T* Pop() {
		std::lock_guard<std::mutex> lock(mutex_);
		if (empty()) {
			return nullptr;
		}

		T* ret = buffers_[head_++];
		head_ %= buffer_size_;

		return ret;
	}

	bool Empty() {
		std::lock_guard<std::mutex> lock(mutex_);
		return empty();
	}

private:
	void enlarge(size_t buffer_size = 1024) {
		std::vector<T*> new_data;
		new_data.resize(buffer_size_ + buffer_size);
		int head = head_, tail = tail_;
		head_ = tail_ = 0;
		for (; head != tail; head = (head + 1) % buffer_size_) {
			new_data[tail_++] = buffers_[head];
		}
		buffer_size_ += buffer_size;
		buffers_ = new_data;
	}

	bool full() {
		return (tail_ + 1) % buffer_size_ == head_;
	}

	bool empty() {
		return buffers_.size() == 0 ||
			buffer_size_ == 0 ||
			head_ == tail_;
	}

private:
	std::vector<T*> buffers_;
	size_t buffer_size_;
	int head_;
	int tail_;
	
	// TODO 暂时瞎搞一个,这样加锁现在是完全没有ringbuffer的效果的,之后有时间再改
	std::mutex mutex_;
};
} // namespace ringbuffer