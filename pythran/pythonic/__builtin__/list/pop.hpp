#ifndef PYTHONIC_BUILTIN_LIST_POP_HPP
#define PYTHONIC_BUILTIN_LIST_POP_HPP

#include "pythonic/include/__builtin__/list/pop.hpp"

#include "pythonic/__dispatch__/pop.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace list {

            ALIAS(pop, pythonic::__dispatch__::pop);

            PROXY_IMPL(pythonic::__builtin__::list, pop);
        }
    }

}
#endif
