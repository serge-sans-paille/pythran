#ifndef PYTHONIC_NUMPY_FABS_HPP
#define PYTHONIC_NUMPY_FABS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/abs.hpp"

namespace pythonic {

    namespace numpy {

            ALIAS(fabs, abs)
            PROXY(pythonic::numpy, fabs);

    }
}

#endif
