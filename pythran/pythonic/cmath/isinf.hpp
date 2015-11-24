#ifndef PYTHONIC_CMATH_ISINF_HPP
#define PYTHONIC_CMATH_ISINF_HPP

#include "pythonic/include/cmath/isinf.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    DEFINE_FUNCTOR_2(isinf, std::isinf);
  }
}

#endif
