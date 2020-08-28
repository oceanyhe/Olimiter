// This is the demo version for Olimiter, a free, open source server access limiter tool
// author: oceanyhe
// last updated: 2020-08-28

#pragma once

#include <atomic>

#include "limiter.h"

namespace Olimiter {

class SmoothLimiter : public Limiter {
  public:
    explicit SmoothLimiter(int64_t limit, int32_t fps_num = 100);

    ~ SmoothLimiter() {}

    int64_t CheckLimit(int64_t quest_num) override;

    int64_t GetCurrLoad() override;

    int64_t GetMaxLimit() override;

  private:
    int64_t limit_;
    int64_t curr_count_;
    int64_t last_access_time_;
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;

};  // class SmoothLimiter

using SmoothLimiterPtr = std::shared_ptr<SmoothLimiter>;

}  // namespace Olimiter