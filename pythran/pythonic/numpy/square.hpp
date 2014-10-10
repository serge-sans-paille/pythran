#ifndef PYTHONIC_NUMPY_SQUARE_HPP
#define PYTHONIC_NUMPY_SQUARE_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/sqr.hpp>

#ifdef USE_GMP
#include "pythonic/types/long.hpp"

namespace nt2 {
    template<class T, class U>
        auto sqr(__gmp_expr<T,U> const& a) -> decltype(a * a) {
            return a * a;
        }
}

#endif

namespace pythonic {

    namespace numpy {

#define NUMPY_UNARY_FUNC_NAME square
#define NUMPY_UNARY_FUNC_SYM nt2::sqr
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

