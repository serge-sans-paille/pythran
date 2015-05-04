#ifndef PYTHONIC_INCLUDE_NUMPY_FIX_HPP
#define PYTHONIC_INCLUDE_NUMPY_FIX_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/trunc.hpp>

namespace pythonic {

    namespace numpy {
        namespace wrapper {
            template<class T>
                double fix(T const& v);
        }
#define NUMPY_NARY_FUNC_NAME fix
#define NUMPY_NARY_FUNC_SYM wrapper::fix
#include "pythonic/include/types/numpy_nary_expr.hpp"

    }

}

#endif
