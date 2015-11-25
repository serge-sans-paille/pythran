#ifndef PYTHONIC_INCLUDE_OPERATOR_ABS_HPP
#define PYTHONIC_INCLUDE_OPERATOR_ABS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/__builtin__/abs.hpp"

namespace pythonic
{

  namespace operator_
  {
    USING_FUNCTOR(abs, __builtin__::functor::abs);
  }
}

#endif
