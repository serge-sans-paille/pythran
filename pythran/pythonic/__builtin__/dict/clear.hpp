#ifndef PYTHONIC_BUILTIN_DICT_CLEAR_HPP
#define PYTHONIC_BUILTIN_DICT_CLEAR_HPP

#include "pythonic/__dispatch__/clear.hpp"
#include "pythonic/include/__builtin__/dict/clear.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            ALIAS(clear, pythonic::__dispatch__::clear);

            PROXY_IMPL(pythonic::__builtin__::dict, clear);
        }
    }
}

#endif
