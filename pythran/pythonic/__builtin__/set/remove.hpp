#ifndef PYTHONIC_BUILTIN_SET_REMOVE_HPP
#define PYTHONIC_BUILTIN_SET_REMOVE_HPP

#include "pythonic/include/__builtin__/set/remove.hpp"

#include "pythonic/__dispatch__/remove.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            ALIAS(remove, pythonic::__dispatch__::remove);

            PROXY_IMPL(pythonic::__builtin__::set, remove);
        }
    }

}
#endif 

