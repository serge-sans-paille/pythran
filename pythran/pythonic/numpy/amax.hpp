#ifndef PYTHONIC_NUMPY_AMAX_HPP
#define PYTHONIC_NUMPY_AMAX_HPP

#include "pythonic/include/numpy/amax.hpp"

#include "pythonic/numpy/max.hpp"

namespace pythonic {

    namespace numpy {

        FPROXY_IMPL(pythonic::numpy, amax, max);

    }

}

#endif
