#ifndef PYTHONIC_NUMPY_LOGICALXOR_HPP
#define PYTHONIC_NUMPY_LOGICALXOR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        namespace wrapper {
        template<class T0, class T1>
            auto logical_xor(T0 const& t0, T1 const& t1) -> decltype((t0 and not t1) or (t1 and not t0)) {
                return (t0 and not t1) or (t1 and not t0);
            }
        }
#define NUMPY_BINARY_FUNC_NAME logical_xor
#define NUMPY_BINARY_FUNC_SYM wrapper::logical_xor
#include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

