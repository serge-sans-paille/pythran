#ifndef PYTHONIC_LIST_COUNT_HPP
#define PYTHONIC_LIST_COUNT_HPP

#include "pythonic/__dispatch__/count.hpp"

namespace pythonic {

    namespace __list__ {
        ALIAS(count, pythonic::__dispatch__::count);
        PROXY(pythonic::__list__, count);
    }
}

#endif



