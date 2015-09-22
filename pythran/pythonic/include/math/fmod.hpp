#ifndef PYTHONIC_INCLUDE_MATH_FMOD_HPP
#define PYTHONIC_INCLUDE_MATH_FMOD_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(fmod, std::fmod);
    PROXY_DECL(pythonic::math, fmod);
  }
}

#endif
