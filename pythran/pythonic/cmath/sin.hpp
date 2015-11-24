#ifndef PYTHONIC_CMATH_SIN_HPP
#define PYTHONIC_CMATH_SIN_HPP

#include "pythonic/include/cmath/sin.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DEFINE_FUNCTOR_2(sin, std::sin);
  }
}

#endif
