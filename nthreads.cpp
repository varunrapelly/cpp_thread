
#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

#ifndef MAX_CNT
#define MAX_CNT 10
#endif

#ifndef NT
#define NT 2
#endif

volatile int cnt = 0;
volatile int thread_cnt = 0;
std::mutex cnt_mutex;
std::condition_variable m_next;

void thread_fun(int i)
{
	auto thread_id = i;
	while (1)
	{
		std::unique_lock<std::mutex> mlock(cnt_mutex);
		while (thread_id != thread_cnt)
		{
			//std::cout << thread_id << " Waiting for my turn \t";
			m_next.wait(mlock);
		}	
	
		thread_cnt++;
		if (thread_cnt == NT)
		{
			thread_cnt = 0;
		}
		if (cnt >= MAX_CNT)
		{
			m_next.notify_all();
			break;
		}
		std::cout<< "ID: " << thread_id << " CNT: " << cnt << std::endl;
		cnt++;
		m_next.notify_all();
	}
}

int main()
{
	std::thread t[NT];
	for (auto i = 0; i < NT; i++)
		t[i]= std::thread(thread_fun, i);
	for (auto i = 0; i < NT; i++)
		t[i].join();
	return 0;
}
