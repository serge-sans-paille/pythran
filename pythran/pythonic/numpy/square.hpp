#ifndef PYTHONIC_NUMPY_SQUARE_HPP
#define PYTHONIC_NUMPY_SQUARE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            auto square(T const& t) -> decltype(t*t) {
                return t*t;
            }

        namespace wrapper {
            PROXY(pythonic::numpy, square)

        }
#define NUMPY_UNARY_FUNC_NAME square
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::square
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, square)

    }

}

#endif

