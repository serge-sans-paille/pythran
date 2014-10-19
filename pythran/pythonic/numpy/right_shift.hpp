#ifndef PYTHONIC_NUMPY_RIGHTSHIFT_HPP
#define PYTHONIC_NUMPY_RIGHTSHIFT_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include "pythonic/operator_/rshift.hpp"

namespace pythonic {

    namespace numpy {
    #define NUMPY_BINARY_FUNC_NAME right_shift
    #define NUMPY_BINARY_FUNC_SYM operator_::rshift
    #include "pythonic/types/numpy_binary_expr.hpp"
    }

}

#endif

