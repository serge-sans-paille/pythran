#ifndef PYTHONIC_INCLUDE_NUMPY_ARRAYSTR_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARRAYSTR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/array2string.hpp"

namespace pythonic {

    namespace numpy {

        ALIAS_DECL(array_str, array2string);
        PROXY_DECL(pythonic::numpy, array_str);

    }
}

#endif
