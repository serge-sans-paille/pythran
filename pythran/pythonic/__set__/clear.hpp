#ifndef PYTHONIC_SET_CLEAR_HPP
#define PYTHONIC_SET_CLEAR_HPP

#include "pythonic/__dispatch__/clear.hpp"

namespace pythonic {

    namespace __set__ {
        ALIAS(clear, pythonic::__dispatch__::clear);
        PROXY(pythonic::__set__, clear);
    }
}

#endif
