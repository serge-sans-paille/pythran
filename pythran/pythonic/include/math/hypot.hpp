#ifndef PYTHONIC_INCLUDE_MATH_HYPOT_HPP
#define PYTHONIC_INCLUDE_MATH_HYPOT_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

#undef hypot
// This is a windows defined macro that clash with std::hypot and our hypot
// function

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(hypot, std::hypot);
  }
}

#endif
