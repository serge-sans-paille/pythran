#ifndef PYTHONIC_NUMPY_LOGICALNOT_HPP
#define PYTHONIC_NUMPY_LOGICALNOT_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/operator_/not_.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_NARY_FUNC_NAME logical_not
    #define NUMPY_NARY_FUNC_SYM pythonic::operator_::not_
    #include "pythonic/types/numpy_nary_expr.hpp"

    }

}

#endif

