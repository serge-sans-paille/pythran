#ifndef PYTHONIC_INCLUDE_NUMPY_UINT16_HPP
#define PYTHONIC_INCLUDE_NUMPY_UINT16_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/meta.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_op_helper.hpp"

namespace pythonic {

    namespace numpy {

        namespace details {

            uint16_t uint16();
            template<class V>
                uint16_t uint16(V v);
        }

#define NUMPY_NARY_FUNC_NAME uint16
#define NUMPY_NARY_FUNC_SYM details::uint16
#include "pythonic/include/types/numpy_nary_expr.hpp"


    }

}

#endif

