#ifndef PYTHONIC_DICT_POP_HPP
#define PYTHONIC_DICT_POP_HPP

#include "pythonic/__dispatch__/pop.hpp"

namespace pythonic {
namespace __builtin__ {

    namespace dict {
        ALIAS(pop, pythonic::__dispatch__::pop);
        PROXY(pythonic::__builtin__::dict, pop);
    }
    }
}

#endif

