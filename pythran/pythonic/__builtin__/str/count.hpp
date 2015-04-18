#ifndef PYTHONIC_BUILTIN_STR_COUNT_HPP
#define PYTHONIC_BUILTIN_STR_COUNT_HPP

#include "pythonic/include/__builtin__/str/count.hpp"

#include "pythonic/__dispatch__/count.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            ALIAS(count, pythonic::__dispatch__::count);

            PROXY_IMPL(pythonic::__builtin__::str, count);
        }
    }

}
#endif
