// This is the demo version for Olimiter, a free, open source server access limiter tool
// author: oceanyhe
// last updated: 2020-08-28

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

#include "seconds_limiter.h"

#define THREAD_NUM      10
#define THREAD_COUNT    1000000
#define LIMIT           1000

void MultiThreadLimiterTest(std::atomic<int32_t> *count, Olimiter::SecondsLimiterPtr limiter) {
  for (int i = 0; i < THREAD_COUNT; ++i) {
    if (limiter->CheckLimit(1)) {
      ++(*count);
    }
  }
  return ;
}

int main() {
  int64_t start_time = Olimiter::GetSystemTimeMilliseconds();

  Olimiter::SecondsLimiterPtr limiter = std::make_shared<Olimiter::SecondsLimiter>(LIMIT);
  std::atomic<int32_t> count{0};

  std::vector<std::thread> thread_lists;
  for (int i = 0; i < THREAD_NUM; ++i) {
    thread_lists.push_back(std::thread(MultiThreadLimiterTest, &count, limiter));
  }

  for (auto &t : thread_lists) {
    t.join();
  }

  int64_t end_time = Olimiter::GetSystemTimeMilliseconds();
  int64_t time_cost = end_time - start_time;

  std::cout << "total time cost: " << time_cost / 1000.0 << " sec;" << std::endl;
  std::cout << "total request num: " << THREAD_COUNT * THREAD_NUM << std::endl;
  std::cout << "request qps: " << THREAD_COUNT * THREAD_NUM * 1000.0 / time_cost << " quest/sec" << std::endl;
  std::cout << "passed quest: " << count << std::endl;
  std::cout << "passed qps: " << count * 1000.0 / time_cost << " quest/sec" << std::endl;

  return 0;
}