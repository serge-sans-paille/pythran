#ifndef PYTHONIC_CMATH_ACOSH_HPP
#define PYTHONIC_CMATH_ACOSH_HPP

#include "pythonic/include/cmath/acosh.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DEFINE_FUNCTOR_2(acosh, std::acosh);
  }
}

#endif
