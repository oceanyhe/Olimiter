// This is the demo version for Olimiter, a free, open source server access limiter tool
// author: oceanyhe
// last updated: 2020-08-28

#pragma once

#include <atomic>
#include <mutex>

#include "limiter.h"

namespace Olimiter {

class SecondsLimiter : public Limiter {
  public:
    explicit SecondsLimiter(int64_t limit);

    ~SecondsLimiter() {}

    int64_t CheckLimit(int64_t quest_num) override;

    int64_t GetCurrLoad() override;

    int64_t GetMaxLimit() override;

  private:
    int64_t limit_;
    std::atomic<int64_t> curr_count_;
    int64_t last_access_time_;
    std::mutex lock_;

};  // class SecondsLimiter

using SecondsLimiterPtr = std::shared_ptr<SecondsLimiter>;

}  // namespace Olimiter