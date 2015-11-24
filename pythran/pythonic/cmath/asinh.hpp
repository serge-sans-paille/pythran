#ifndef PYTHONIC_CMATH_ASINH_HPP
#define PYTHONIC_CMATH_ASINH_HPP

#include "pythonic/include/cmath/asinh.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DEFINE_FUNCTOR_2(asinh, std::asinh);
  }
}

#endif
