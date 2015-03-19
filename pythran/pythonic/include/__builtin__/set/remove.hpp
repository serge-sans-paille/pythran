#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_REMOVE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_REMOVE_HPP

#include "pythonic/__dispatch__/remove.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            ALIAS_DECL(remove, pythonic::__dispatch__::remove);

            PROXY_DECL(pythonic::__builtin__::set, remove);
        }
    }

}
#endif 
