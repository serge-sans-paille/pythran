#ifndef PYTHONIC_MODULE_TIME_H
#define PYTHONIC_MODULE_TIME_H

#include <time.h>
#include <sys/time.h>
#include <cmath>

namespace pythonic {
    namespace time {
       none_type sleep(double const value)
       {
            struct timespec t;
            t.tv_sec = std::fabs(value);
            t.tv_nsec = std::fabs((value - t.tv_sec) * 1e+9);
            nanosleep(&t, nullptr);
            return __builtin__::None;
       }    
       PROXY(pythonic::time, sleep)

       double time()
       {
            struct timeval t;
            gettimeofday(&t, nullptr);
            return t.tv_sec + t.tv_usec * 1e-6;
       }    
       PROXY(pythonic::time, time)
    }
}

#endif
