#ifndef PYTHONIC_NUMPY_LOGICALAND_HPP
#define PYTHONIC_NUMPY_LOGICALAND_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T0, class T1>
            auto logical_and(T0 const& t0, T1 const& t1) -> decltype(t0 and t1) {
                return t0 and t1;
            }

        namespace wrapper {
            PROXY(pythonic::numpy, logical_and)
        }
#define NUMPY_BINARY_FUNC_NAME logical_and
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::logical_and
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, logical_and)

    }

}

#endif

