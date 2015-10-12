#ifndef PYTHONIC_INCLUDE_CMATH_EXP_HPP
#define PYTHONIC_INCLUDE_CMATH_EXP_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS_DECL(exp, std::exp);
    PROXY_DECL(pythonic::cmath, exp);
  }
}

#endif
