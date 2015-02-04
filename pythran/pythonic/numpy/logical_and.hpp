#ifndef PYTHONIC_NUMPY_LOGICALAND_HPP
#define PYTHONIC_NUMPY_LOGICALAND_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"

namespace pythonic {

    namespace numpy {

        namespace wrapper {
        template<class T0, class T1>
            auto logical_and(T0 const& t0, T1 const& t1) -> decltype(t0 and t1) {
                return t0 and t1;
            }
        }
#define NUMPY_NARY_FUNC_NAME logical_and
#define NUMPY_NARY_FUNC_SYM wrapper::logical_and
#include "pythonic/types/numpy_nary_expr.hpp"

    }

}

#endif

