#ifndef PYTHONIC_CMATH_ATAN_HPP
#define PYTHONIC_CMATH_ATAN_HPP

#include "pythonic/include/cmath/atan.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DEFINE_FUNCTOR_2(atan, std::atan);
  }
}

#endif
