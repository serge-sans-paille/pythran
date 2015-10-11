#ifndef PYTHONIC_CMATH_EXP_HPP
#define PYTHONIC_CMATH_EXP_HPP

#include "pythonic/include/cmath/exp.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(exp, std::exp);
    PROXY_IMPL(pythonic::cmath, exp);
  }
}

#endif
