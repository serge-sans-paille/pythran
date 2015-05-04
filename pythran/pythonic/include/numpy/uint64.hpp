#ifndef PYTHONIC_INCLUDE_NUMPY_UINT64_HPP
#define PYTHONIC_INCLUDE_NUMPY_UINT64_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/meta.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_op_helper.hpp"

namespace pythonic {

    namespace numpy {

        namespace details {

            uint64_t uint64();
            template<class V>
                uint64_t uint64(V v);
        }

#define NUMPY_NARY_FUNC_NAME uint64
#define NUMPY_NARY_FUNC_SYM details::uint64
#include "pythonic/include/types/numpy_nary_expr.hpp"


    }

}

#endif

