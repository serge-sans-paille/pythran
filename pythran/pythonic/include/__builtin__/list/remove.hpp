#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_REMOVE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_REMOVE_HPP

#include "pythonic/__dispatch__/remove.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace list {

            ALIAS_DECL(remove, pythonic::__dispatch__::remove);

            PROXY_DECL(pythonic::__builtin__::list, remove);
        }
    }

}
#endif
