#ifndef PYTHONIC_BUILTIN_SET_CLEAR_HPP
#define PYTHONIC_BUILTIN_SET_CLEAR_HPP

#include "pythonic/include/__builtin__/set/clear.hpp"

#include "pythonic/__dispatch__/clear.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            ALIAS(clear, pythonic::__dispatch__::clear);

            PROXY_IMPL(pythonic::__builtin__::set, clear);
        }
    }

}
#endif 
