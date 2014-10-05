#ifndef PYTHONIC_NUMPY_SORTCOMPLEX_HPP
#define PYTHONIC_NUMPY_SORTCOMPLEX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/sort.hpp"

namespace pythonic {

    namespace numpy {

            ALIAS(sort_complex, sort)
            PROXY(pythonic::numpy, sort_complex);

    }
}

#endif

