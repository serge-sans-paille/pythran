#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_CLEAR_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_CLEAR_HPP

#include "pythonic/__dispatch__/clear.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            ALIAS_DECL(clear, pythonic::__dispatch__::clear);

            PROXY_DECL(pythonic::__builtin__::dict, clear);
        }
    }
}

#endif

