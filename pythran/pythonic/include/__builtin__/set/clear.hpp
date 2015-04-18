#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_CLEAR_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_CLEAR_HPP

#include "pythonic/__dispatch__/clear.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            ALIAS_DECL(clear, pythonic::__dispatch__::clear);

            PROXY_DECL(pythonic::__builtin__::set, clear);
        }
    }

}
#endif 
