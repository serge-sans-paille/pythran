#ifndef PYTHONIC_NUMPY_POWER_HPP
#define PYTHONIC_NUMPY_POWER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/pow.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(power, nt2::pow)

            namespace wrapper {
                PROXY(pythonic::numpy, power)
            }
#define NUMPY_BINARY_FUNC_NAME power
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::power
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, power)
    }
}

#endif

