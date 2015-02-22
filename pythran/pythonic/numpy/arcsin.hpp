#ifndef PYTHONIC_NUMPY_ARCSIN_HPP
#define PYTHONIC_NUMPY_ARCSIN_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/asin.hpp>

namespace nt2 {
double asin(long l) { return asin(static_cast<double>(l)); }
}

namespace pythonic {

    namespace numpy {
#define NUMPY_NARY_FUNC_NAME arcsin
#define NUMPY_NARY_FUNC_SYM nt2::asin
#include "pythonic/types/numpy_nary_expr.hpp"
    }
}

#endif

