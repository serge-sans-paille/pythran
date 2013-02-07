#ifndef PYTHONIC_MODULE_TIME_H
#define PYTHONIC_MODULE_TIME_H

#include <time.h>
#include <cmath>

namespace pythonic {
    namespace time {
       none_type sleep(double const value)
       {
            struct timespec t;
            t.tv_sec = std::fabs(value);
            t.tv_nsec = std::fabs((value - t.tv_sec) * 1e+9);
            nanosleep(&t, nullptr);
            return None;
       }    
    }
}

#endif
