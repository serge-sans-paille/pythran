#ifndef PYTHONIC_CMATH_TANH_HPP
#define PYTHONIC_CMATH_TANH_HPP

#include "pythonic/include/cmath/tanh.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DEFINE_FUNCTOR_2(tanh, std::tanh);
  }
}

#endif
