#ifndef PYTHONIC_DICT_COPY_HPP
#define PYTHONIC_DICT_COPY_HPP

#include "pythonic/__dispatch__/copy.hpp"

namespace pythonic {
namespace __builtin__ {
    namespace dict {
        ALIAS(copy, pythonic::__dispatch__::copy);
        PROXY(pythonic::__builtin__::dict, copy);
    }
}
}

#endif

