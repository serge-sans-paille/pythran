#ifndef PYTHONIC_MATH_ISINF_HPP
#define PYTHONIC_MATH_ISINF_HPP

#include "pythonic/include/math/isinf.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(isinf, std::isinf);
  }
}

#endif
