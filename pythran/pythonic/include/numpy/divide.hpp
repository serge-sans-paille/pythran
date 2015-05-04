#ifndef PYTHONIC_INCLUDE_NUMPY_DIVIDE_HPP
#define PYTHONIC_INCLUDE_NUMPY_DIVIDE_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/operator_/div.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_NARY_FUNC_NAME divide
    #define NUMPY_NARY_FUNC_SYM pythonic::operator_::div
    #include "pythonic/include/types/numpy_nary_expr.hpp"

    }

}

#endif

