#ifndef PYTHONIC_NUMPY_ABSOLUTE_HPP
#define PYTHONIC_NUMPY_ABSOLUTE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/abs.hpp"

namespace pythonic {

    namespace numpy {

            ALIAS(absolute, abs)
            PROXY(pythonic::numpy, absolute);

    }
}

#endif

