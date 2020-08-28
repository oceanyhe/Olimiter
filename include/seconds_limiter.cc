// This is the demo version for Olimiter, a free, open source server access limiter tool
// author: oceanyhe
// last updated: 2020-08-28

#include "seconds_limiter.h"

namespace Olimiter {

SecondsLimiter::SecondsLimiter(int64_t limit) : limit_(limit) {
  curr_count_ = 0;
  last_access_time_ = GetSystemTimeMilliseconds();
}

int64_t SecondsLimiter::CheckLimit(int64_t quest_num) {
  // mutex version
  int64_t nows = GetSystemTimeMilliseconds();

  if (nows - last_access_time_ > 1000) {
    lock_.lock();
    if (nows - last_access_time_ > 1000) {
      // double check
      int32_t times = static_cast<int32_t>((nows - last_access_time_) / 1000);
      last_access_time_ += 1000 * times;
      curr_count_ = 0;
    }
    lock_.unlock();
  }

  if (++curr_count_ > limit_) {
    return OlimiterAccessDenied;
  } else {
    return OlimiterAccessAllow;
  }
}

int64_t SecondsLimiter::GetCurrLoad() { return curr_count_; }

int64_t SecondsLimiter::GetMaxLimit() { return limit_; }

}  // namespace Olimiter