#ifndef PYTHONIC_MATH_FMOD_HPP
#define PYTHONIC_MATH_FMOD_HPP

#include "pythonic/include/math/fmod.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(fmod, std::fmod);
  }
}

#endif
