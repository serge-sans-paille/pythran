#ifndef PYTHONIC_SET_COPY_HPP
#define PYTHONIC_SET_COPY_HPP

#include "pythonic/__dispatch__/copy.hpp"

namespace pythonic {

    namespace __set__ {
        ALIAS(copy, pythonic::__dispatch__::copy);
        PROXY(pythonic::__set__, copy);
    }
}

#endif


