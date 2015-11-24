#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_COPY_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_COPY_HPP

#include "pythonic/include/__dispatch__/copy.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{
  namespace __builtin__
  {
    namespace set
    {
      USING_FUNCTOR(copy, pythonic::__dispatch__::functor::copy);
    }
  }
}
#endif
