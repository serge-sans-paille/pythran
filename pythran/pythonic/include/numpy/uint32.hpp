#ifndef PYTHONIC_INCLUDE_NUMPY_UINT32_HPP
#define PYTHONIC_INCLUDE_NUMPY_UINT32_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/meta.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_op_helper.hpp"

namespace pythonic {

    namespace numpy {

        namespace details {

            uint32_t uint32();
            template<class V>
                uint32_t uint32(V v);
        }

#define NUMPY_NARY_FUNC_NAME uint32
#define NUMPY_NARY_FUNC_SYM details::uint32
#include "pythonic/include/types/numpy_nary_expr.hpp"

    }

}

#endif

