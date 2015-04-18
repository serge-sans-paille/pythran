#ifndef PYTHONIC_BUILTIN_LIST_REMOVE_HPP
#define PYTHONIC_BUILTIN_LIST_REMOVE_HPP

#include "pythonic/include/__builtin__/list/remove.hpp"

#include "pythonic/__dispatch__/remove.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace list {

            ALIAS(remove, pythonic::__dispatch__::remove);

            PROXY_IMPL(pythonic::__builtin__::list, remove);
        }
    }

}
#endif
