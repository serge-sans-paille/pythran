#ifndef PYTHONIC_SET_REMOVE_HPP
#define PYTHONIC_SET_REMOVE_HPP

#include "pythonic/__dispatch__/remove.hpp"

namespace pythonic {

    namespace __set__ {
        ALIAS(remove, pythonic::__dispatch__::remove);
        PROXY(pythonic::__set__, remove);
    }
}

#endif

