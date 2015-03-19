#ifndef PYTHONIC_BUILTIN_DICT_COPY_HPP
#define PYTHONIC_BUILTIN_DICT_COPY_HPP

#include "pythonic/__dispatch__/copy.hpp"
#include "pythonic/include/__builtin__/dict/copy.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            ALIAS(copy, pythonic::__dispatch__::copy);

            PROXY_IMPL(pythonic::__builtin__::dict, copy);
        }
    }
}

#endif
