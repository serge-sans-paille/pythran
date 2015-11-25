#ifndef PYTHONIC_INCLUDE_MATH_LDEXP_HPP
#define PYTHONIC_INCLUDE_MATH_LDEXP_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(ldexp, std::ldexp);
  }
}

#endif
