#ifndef PYTHONIC_CMATH_LOG10_HPP
#define PYTHONIC_CMATH_LOG10_HPP

#include "pythonic/include/cmath/log10.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DEFINE_FUNCTOR_2(log10, std::log10);
  }
}

#endif
