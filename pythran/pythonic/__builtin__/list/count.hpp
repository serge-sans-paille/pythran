#ifndef PYTHONIC_BUILTIN_LIST_COUNT_HPP
#define PYTHONIC_BUILTIN_LIST_COUNT_HPP

#include "pythonic/__dispatch__/count.hpp"

#include "pythonic/include/__builtin__/list/count.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace list {

            ALIAS(count, pythonic::__dispatch__::count);

            PROXY_IMPL(pythonic::__builtin__::list, count);
        }

    }

}

#endif
