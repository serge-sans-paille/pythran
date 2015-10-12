#ifndef PYTHONIC_INCLUDE_CMATH_ISINF_HPP
#define PYTHONIC_INCLUDE_CMATH_ISINF_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS_DECL(isinf, std::isinf);
    PROXY_DECL(pythonic::cmath, isinf);
  }
}

#endif
