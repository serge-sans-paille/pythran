#ifndef PYTHONIC_DICT_COPY_HPP
#define PYTHONIC_DICT_COPY_HPP

#include "pythonic/__dispatch__/copy.hpp"

namespace pythonic {

    namespace __dict__ {
        ALIAS(copy, pythonic::__dispatch__::copy);
        PROXY(pythonic::__dict__, copy);
    }
}

#endif

