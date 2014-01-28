#ifndef PYTHONIC_NUMPY_EXP_HPP
#define PYTHONIC_NUMPY_EXP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/exp.hpp>


namespace pythonic {

    namespace numpy {
        using nt2::exp;

        namespace wrapper {
            PROXY(pythonic::numpy, exp)

        }
#define NUMPY_UNARY_FUNC_NAME exp
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::exp
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, exp)

    }

}

#endif

