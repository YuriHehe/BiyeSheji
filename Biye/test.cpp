#include"test.h"
#include"log.h"
#include"conf.h"
#include"BitmapMgr.h"
#include"threadpool.h"
#include"adloadtask.h"

namespace test {
void Test()
{
	RingBuffer_test();

	Bitmap_test();

	ThreadPool_test();

	Adload_test();
}

void RingBuffer_test()
{
	std::vector<int> check;
	ringbuffer::RingBuffer<int> a(1024);
	for (int i = 0; i < 5000; ++i) {
		int* b = new int(i);
		a.Push(b);
		check.push_back(i);
	}

	std::vector<std::future<int>> vec;
	for (int i = 0; i < 100; ++i) {
		vec.push_back(std::async(std::launch::async, [&]() {
			int tmp = rand() % 1000;
			for (int i = 0; i < tmp; ++i) {
				int c = int(3 * 3123.321);
				int* b = a.Pop();
				if (b != nullptr) {
					a.Push(b);
				}
			}
			return 0;
		}));
	}
	for (auto& f : vec) {
		f.wait();
	}

	std::vector<int> res;
	int* p;
	while ((p = a.Pop()) != nullptr) {
		res.push_back(*p);
		delete p;
		p = nullptr;
	}
	std::sort(res.begin(), res.end());
	bool flag = true;
	if (res.size() != check.size()) {
		flag = false;
	}
	for (size_t i = 0; i < res.size() && i < check.size(); ++i) {
		if (res[i] != check[i]) {
			flag = false;
		}
	}
	if (!flag) {
		INFO_LOG("\n-------------------ERROR-------------------");
	}
	else {
		INFO_LOG("\n-------------------SUCCESS-------------------");
	}
}
void Bitmap_test()
{
	auto b1 = bitmap::BitmapMgr::instance()->allocate();
	auto b2 = bitmap::BitmapMgr::instance()->allocate();
	b1->Set(1, 1);
	b2->Set(2, 1);
	b1->Union(*b2);
	b2->Intersect(*b1);
	if (b1->nbit() == 2 && b2->nbit() == 1) {
		INFO_LOG("\n-------------------SUCCESS-------------------");
	}
	else {
		INFO_LOG("\n-------------------ERROR-------------------");
	}
}
void ThreadPool_test()
{
	thread::ThreadPool pool(5);
	std::vector<std::future<int>> vec;
	for (int i = 0; i < 10; ++i) {
		vec.push_back(pool.enqueue([i](){
			INFO_LOG("hello " + std::to_string(i));
			std::this_thread::sleep_for(std::chrono::seconds(3));
			INFO_LOG("world " + std::to_string(i));
			return 0;
		}));
	}
	for (auto && result : vec) {
		INFO_LOG("res " + std::to_string(result.get()));
	}
	INFO_LOG("\n-------------------SUCCESS-------------------");
}
void Adload_test()
{
	Task::AdloadTask::instance()->run();

	std::this_thread::sleep_for(std::chrono::seconds(5));

	Task::AdloadTask::instance()->stop();

	INFO_LOG("\n-------------------SUCCESS-------------------");
}
}