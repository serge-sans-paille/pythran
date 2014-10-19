#ifndef PYTHONIC_NUMPY_TRUEDIVIDE_HPP
#define PYTHONIC_NUMPY_TRUEDIVIDE_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/operator_/div.hpp"

namespace pythonic {

    namespace numpy {

    // FIXME: this is not always a true_divide...
    #define NUMPY_BINARY_FUNC_NAME true_divide
    #define NUMPY_BINARY_FUNC_SYM pythonic::operator_::div
    #include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

