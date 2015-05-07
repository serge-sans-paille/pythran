#ifndef PYTHONIC_NUMPY_INNER_HPP
#define PYTHONIC_NUMPY_INNER_HPP

#include "pythonic/include/numpy/inner.hpp"

#include "pythonic/numpy/dot.hpp"

namespace pythonic {

    namespace numpy {

        FPROXY_IMPL(pythonic::numpy, inner, dot);

    }

}

#endif
