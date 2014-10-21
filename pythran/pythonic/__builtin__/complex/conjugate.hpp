#ifndef PYTHONIC_COMPLEX_CONJUGATE_HPP
#define PYTHONIC_COMPLEX_CONJUGATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/conjugate.hpp"

namespace pythonic { namespace __builtin__  {

    namespace complex {
        ALIAS(conjugate, numpy::proxy::conjugate{});
        PROXY(pythonic::__builtin__::complex, conjugate);
    }

}

}
#endif

