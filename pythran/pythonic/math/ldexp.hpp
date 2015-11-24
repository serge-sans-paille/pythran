#ifndef PYTHONIC_MATH_LDEXP_HPP
#define PYTHONIC_MATH_LDEXP_HPP

#include "pythonic/include/math/ldexp.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(ldexp, std::ldexp);
  }
}

#endif
