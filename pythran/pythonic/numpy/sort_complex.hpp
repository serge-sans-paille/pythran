#ifndef PYTHONIC_NUMPY_SORTCOMPLEX_HPP
#define PYTHONIC_NUMPY_SORTCOMPLEX_HPP

#include "pythonic/include/numpy/sort_complex.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/sort.hpp"

namespace pythonic {

    namespace numpy {

            ALIAS(sort_complex, sort)
            PROXY_IMPL(pythonic::numpy, sort_complex);

    }
}

#endif
