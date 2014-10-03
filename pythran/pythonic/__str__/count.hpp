#ifndef PYTHONIC_STR_COUNT_HPP
#define PYTHONIC_STR_COUNT_HPP

#include "pythonic/__dispatch__/count.hpp"

namespace pythonic {

    namespace __str__ {
        ALIAS(count, pythonic::__dispatch__::count);
        PROXY(pythonic::__str__, count);
    }
}

#endif

