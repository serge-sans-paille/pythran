#ifndef PYTHONIC_NUMPY_POWER_HPP
#define PYTHONIC_NUMPY_POWER_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include <nt2/include/functions/pow.hpp>

namespace nt2 {
// See https://github.com/MetaScale/nt2/issues/794
double pow(long n, double m) { return pow(static_cast<double>(n), m); }
long pow(long n, long m) { return std::pow(n, m); }
}

namespace pythonic {

    namespace numpy {
#define NUMPY_NARY_FUNC_NAME power
#define NUMPY_NARY_FUNC_SYM nt2::pow
#include "pythonic/types/numpy_nary_expr.hpp"
    }
}

#endif

