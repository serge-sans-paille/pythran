#ifndef PYTHONIC_DICT_CLEAR_HPP
#define PYTHONIC_DICT_CLEAR_HPP

#include "pythonic/__dispatch__/clear.hpp"

namespace pythonic {
namespace __builtin__ {
    namespace dict {
        ALIAS(clear, pythonic::__dispatch__::clear);
        PROXY(pythonic::__builtin__::dict, clear);
    }
}
}

#endif
