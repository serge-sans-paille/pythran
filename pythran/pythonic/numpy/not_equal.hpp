#ifndef PYTHONIC_NUMPY_NOTEQUAL_HPP
#define PYTHONIC_NUMPY_NOTEQUAL_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/operator_/ne.hpp"

namespace pythonic {

    namespace numpy {
    #define NUMPY_NARY_FUNC_NAME not_equal
    #define NUMPY_NARY_FUNC_SYM pythonic::operator_::ne
    #include "pythonic/types/numpy_nary_expr.hpp"

    }

}

#endif

