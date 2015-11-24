#ifndef PYTHONIC_CMATH_ISNAN_HPP
#define PYTHONIC_CMATH_ISNAN_HPP

#include "pythonic/include/cmath/isnan.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DEFINE_FUNCTOR_2(isnan, std::isnan);
  }
}

#endif
