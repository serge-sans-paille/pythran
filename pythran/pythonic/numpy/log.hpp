#ifndef PYTHONIC_NUMPY_LOG_HPP
#define PYTHONIC_NUMPY_LOG_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/log.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::log;

        namespace wrapper {
            PROXY(pythonic::numpy, log)

        }
#define NUMPY_UNARY_FUNC_NAME log
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::log
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, log)

    }

}

#endif

