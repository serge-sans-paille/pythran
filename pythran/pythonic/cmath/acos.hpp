#ifndef PYTHONIC_CMATH_ACOS_HPP
#define PYTHONIC_CMATH_ACOS_HPP

#include "pythonic/include/cmath/acos.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DEFINE_FUNCTOR_2(acos, std::acos);
  }
}

#endif
