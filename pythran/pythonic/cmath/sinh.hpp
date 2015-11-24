#ifndef PYTHONIC_CMATH_SINH_HPP
#define PYTHONIC_CMATH_SINH_HPP

#include "pythonic/include/cmath/sinh.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DEFINE_FUNCTOR_2(sinh, std::sinh);
  }
}

#endif
