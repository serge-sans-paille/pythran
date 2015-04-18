#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_POP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_POP_HPP

#include "pythonic/__dispatch__/pop.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace list {

            ALIAS_DECL(pop, pythonic::__dispatch__::pop);

            PROXY_DECL(pythonic::__builtin__::list, pop);
        }

    }

}
#endif
