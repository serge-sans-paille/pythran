#ifndef PYTHONIC_NUMPY_BITWISE_OR_HPP
#define PYTHONIC_NUMPY_BITWISE_OR_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/operator_/or_.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_NARY_FUNC_NAME bitwise_or
    #define NUMPY_NARY_FUNC_SYM pythonic::operator_::or_
    #include "pythonic/types/numpy_nary_expr.hpp"

    }
}

#endif

