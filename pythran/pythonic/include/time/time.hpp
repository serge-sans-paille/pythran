#ifndef PYTHONIC_INCLUDE_TIME_TIME_HPP
#define PYTHONIC_INCLUDE_TIME_TIME_HPP

#include "pythonic/utils/proxy.hpp"

#include <sys/time.h>

namespace pythonic {

    namespace time {

        double time();

        PROXY_DECL(pythonic::time, time)

    }

}

#endif
