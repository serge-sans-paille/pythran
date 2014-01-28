#ifndef PYTHONIC_NUMPY_NEXTAFTER_HPP
#define PYTHONIC_NUMPY_NEXTAFTER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/nextafter.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::nextafter;
        namespace wrapper {
            PROXY(pythonic::numpy, nextafter)
        }
#define NUMPY_BINARY_FUNC_NAME nextafter
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::nextafter
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, nextafter)

    }

}

#endif

