#ifndef PYTHONIC_CMATH_ATANH_HPP
#define PYTHONIC_CMATH_ATANH_HPP

#include "pythonic/include/cmath/atanh.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DEFINE_FUNCTOR_2(atanh, std::atanh);
  }
}

#endif
