#ifndef PYTHONIC_CMATH_ISINF_HPP
#define PYTHONIC_CMATH_ISINF_HPP

#include "pythonic/include/cmath/isinf.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(isinf, std::isinf);
    PROXY_IMPL(pythonic::cmath, isinf);
  }
}

#endif
