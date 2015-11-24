#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_NEXT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_NEXT_HPP

#include "pythonic/include/__dispatch__/next.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{
  namespace __builtin__
  {
    namespace file
    {
      USING_FUNCTOR(next, pythonic::__dispatch__::functor::next);
    }
  }
}
#endif
