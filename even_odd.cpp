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
std::condition_variable cnt_condVar;
std::condition_variable m_next;

void even()
{
	while (cnt < MAX_CNT)
	{
		std::unique_lock<std::mutex> mlock(cnt_mutex);
		std::cout<<"Even CNT: " << cnt <<std::endl;
		cnt++;
		cnt_condVar.notify_one();
		while(cnt%2 == 1)
		{
			cnt_condVar.wait(mlock);//, []{ while (cnt%2 == 0); return true;});
			//std::cout << "Waiting for even condition\n";
		}
	}
}

void odd()
{
	while (cnt < MAX_CNT)
	{
		std::unique_lock<std::mutex> mlock(cnt_mutex);
		while(cnt%2 == 0)
		{
			cnt_condVar.wait(mlock);//, []{ while (cnt%2 == 0); return true;});
			//std::cout << "Waiting for ODD condition\t";
		}
		std::cout<<"Odd CNT: " << cnt <<std::endl;
		cnt++;
		cnt_condVar.notify_one();
		//std::cout << "\t Notified for even condition\n";
		//mlock.unlock();
	}
}

int main()
{
	std::thread t1(even);
	std::thread t2(odd);
	t1.join();
	t2.join();
	return 0;
}
