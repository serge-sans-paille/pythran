#ifndef PYTHONIC_BUILTIN_FLOAT_ISINTEGER_HPP
#define PYTHONIC_BUILTIN_FLOAT_ISINTEGER_HPP

#include "pythonic/include/__builtin__/float_/is_integer.hpp"

#include "pythonic/utils/functor.hpp"

#include <cmath>

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace float_
  {

    bool is_integer(double d)
    {
      return std::trunc(d) == d;
    }

    DEFINE_FUNCTOR(pythonic::__builtin__::float_, is_integer);
  }
}
PYTHONIC_NS_END

#endif
