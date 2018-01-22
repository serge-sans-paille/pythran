#ifndef PYTHONIC_INCLUDE_OPERATOR_ABS__HPP
#define PYTHONIC_INCLUDE_OPERATOR_ABS__HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/__builtin__/abs.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{
  USING_FUNCTOR(__abs__, __builtin__::functor::abs);
}
PYTHONIC_NS_END

#endif
