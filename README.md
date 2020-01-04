# cpp_thread

NT = Number of threads (default 2)
MAX_CNT = Counts upto this number (default 10)

This application creates creates NT threads and counts upto MAX_CNT. 
Execution starts with thread 0 and it increments the count. 
Then it notifies the next thread to start the thread execution.

g++ nthreads.cpp -pthread -DNT=20 -DMAX_CNT=207


g++ even_odd.cpp -pthread -DMAX_CNT=121
