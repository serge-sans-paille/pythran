#ifndef PYTHONIC_INCLUDE_CMATH_ATANH_HPP
#define PYTHONIC_INCLUDE_CMATH_ATANH_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DECLARE_FUNCTOR_2(atanh, std::atanh);
  }
}

#endif
