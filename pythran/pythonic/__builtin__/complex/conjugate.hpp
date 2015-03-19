#ifndef PYTHONIC_BUILTIN_COMPLEX_CONJUGATE_HPP
#define PYTHONIC_BUILTIN_COMPLEX_CONJUGATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/conjugate.hpp"
#include "pythonic/include/__builtin__/complex/conjugate.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace complex {

            ALIAS(conjugate, numpy::proxy::conjugate{});

            PROXY_IMPL(pythonic::__builtin__::complex, conjugate);
        }

    }

}
#endif

