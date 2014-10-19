#ifndef PYTHONIC_COMPLEX_CONJUGATE_HPP
#define PYTHONIC_COMPLEX_CONJUGATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/conjugate.hpp"

namespace pythonic {

    namespace __complex___ {
        ALIAS(conjugate, numpy::proxy::conjugate{});
        PROXY(pythonic::__complex___, conjugate);
    }

}

#endif

