#ifndef PYTHONIC_NUMPY_ARRAYSTR_HPP
#define PYTHONIC_NUMPY_ARRAYSTR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/array2string.hpp"

namespace pythonic {
    namespace numpy {
        ALIAS(array_str, array2string);
        PROXY(pythonic::numpy, array_str);
    }
}

#endif

