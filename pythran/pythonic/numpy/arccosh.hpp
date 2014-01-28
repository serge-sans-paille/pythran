#ifndef PYTHONIC_NUMPY_ARCCOSH_HPP
#define PYTHONIC_NUMPY_ARCCOSH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/acosh.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(arccosh, nt2::acosh)
            namespace wrapper {
                PROXY(pythonic::numpy, arccosh)
            }
#define NUMPY_UNARY_FUNC_NAME arccosh
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::arccosh
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, arccosh)

    }

}

#endif

