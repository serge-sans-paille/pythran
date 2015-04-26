#ifndef PYTHONIC_BUILTIN_SET_COPY_HPP
#define PYTHONIC_BUILTIN_SET_COPY_HPP

#include "pythonic/include/__builtin__/set/copy.hpp"

#include "pythonic/__dispatch__/copy.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            ALIAS(copy, pythonic::__dispatch__::copy);

            PROXY_IMPL(pythonic::__builtin__::set, copy);
        }

    }

}
#endif 
