#ifndef PYTHONIC_INCLUDE_TIME_SLEEP_HPP
#define PYTHONIC_INCLUDE_TIME_SLEEP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace time {
        types::none_type sleep(double const value);

        PROXY_DECL(pythonic::time, sleep)

    }

}

#endif
