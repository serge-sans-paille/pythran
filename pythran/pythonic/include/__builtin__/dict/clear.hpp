#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_CLEAR_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_CLEAR_HPP

#include "pythonic/include/__dispatch__/clear.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{
  namespace __builtin__
  {
    namespace dict
    {
      USING_FUNCTOR(clear, pythonic::__dispatch__::functor::clear);
    }
  }
}

#endif
