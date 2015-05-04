#ifndef PYTHONIC_INCLUDE_NUMPY_UINT8_HPP
#define PYTHONIC_INCLUDE_NUMPY_UINT8_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/meta.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_op_helper.hpp"

namespace pythonic {

    namespace numpy {

        namespace details {

            uint8_t uint8();
            template<class V>
                uint8_t uint8(V v);
        }

#define NUMPY_NARY_FUNC_NAME uint8
#define NUMPY_NARY_FUNC_SYM details::uint8
#include "pythonic/include/types/numpy_nary_expr.hpp"


    }

}

#endif

