// This is the demo version for Olimiter, a free, open source server access limiter tool
// author: oceanyhe
// last updated: 2020-08-28

#pragma once

#include<memory>

#include <stdint.h>
#include <sys/timeb.h>

namespace Olimiter {

enum Judge {
  OlimiterAccessDenied,
  OlimiterAccessAllow,
};

/**
 * @brief main class for all limiter
*/
class Limiter {
  public:
    /**
     * @brief check if the access is allowed.
     * 
     * @return return OlimiterAccessAllow if it is passed,
     *          or OlimiterAccessDenied if it is denied.
    */
    virtual int64_t CheckLimit(int64_t quest_num) = 0;

    /**
     * @brief get the current load for the limiter
     * 
     * @return return number of current load of the limiter,
     *          return -1 if it is full
    */
    virtual int64_t GetCurrLoad() = 0;

    /**
     * @brief get the limiter set by user
     * 
     * @return return the limit value that has been set
    */
    virtual int64_t GetMaxLimit() = 0;

};  // class Limiter

using OlimiterPtr = std::shared_ptr<Limiter>;

inline int64_t GetSystemTimeMilliseconds() {
  struct timeb t;
  ftime(&t);
  return 1000*t.time + t.millitm;
}

}  // namespace Olimiter