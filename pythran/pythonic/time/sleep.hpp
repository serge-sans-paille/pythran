#ifndef PYTHONIC_TIME_SLEEP_HPP
#define PYTHONIC_TIME_SLEEP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/__builtin__/None.hpp"

#include <cmath>
#include <sys/time.h>

namespace pythonic {

    namespace time {
        types::none_type sleep(double const value)
        {
            struct timespec t;
            t.tv_sec = std::fabs(value);
            t.tv_nsec = std::fabs((value - t.tv_sec) * 1e+9);
            nanosleep(&t, nullptr);
            return __builtin__::None;
        }    
        PROXY(pythonic::time, sleep)

    }

}

#endif

