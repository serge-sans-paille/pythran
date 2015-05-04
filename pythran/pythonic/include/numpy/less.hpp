#ifndef PYTHONIC_INCLUDE_NUMPY_LESS_HPP
#define PYTHONIC_INCLUDE_NUMPY_LESS_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/operator_/lt.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_NARY_FUNC_NAME less
    #define NUMPY_NARY_FUNC_SYM pythonic::operator_::lt
    #include "pythonic/include/types/numpy_nary_expr.hpp"

    }

}

#endif

