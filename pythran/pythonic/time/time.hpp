#ifndef PYTHONIC_TIME_TIME_HPP
#define PYTHONIC_TIME_TIME_HPP

#include "pythonic/utils/proxy.hpp"
#include <sys/time.h>

namespace pythonic {

    namespace time {
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

