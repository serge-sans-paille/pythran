#ifndef PYTHONIC_INCLUDE_BUILTIN_FLOAT_ISINTEGER_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FLOAT_ISINTEGER_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace float_
    {

      bool is_integer(double d);

      DECLARE_FUNCTOR(pythonic::__builtin__::float_, is_integer);
    }
  }
}

#endif
