#ifndef PYTHONIC_NUMPY_EMPTYLIKE_HPP
#define PYTHONIC_NUMPY_EMPTYLIKE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            auto empty_like(T const&) -> decltype(T(0)) /* prevents instanciation on a ndarray*/ {
                return T();
            }
        namespace wrapper {
            PROXY(pythonic::numpy, empty_like)
        }
#define NUMPY_UNARY_FUNC_NAME empty_like
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::empty_like
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, empty_like)
    }

}

#endif

