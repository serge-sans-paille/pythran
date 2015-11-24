#ifndef PYTHONIC_CMATH_ASIN_HPP
#define PYTHONIC_CMATH_ASIN_HPP

#include "pythonic/include/cmath/asin.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DEFINE_FUNCTOR_2(asin, std::asin);
  }
}

#endif
