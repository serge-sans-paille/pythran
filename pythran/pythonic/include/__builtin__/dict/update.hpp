#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_UPDATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_UPDATE_HPP

#include "pythonic/include/__dispatch__/update.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{
  namespace __builtin__
  {
    namespace dict
    {
      USING_FUNCTOR(update, pythonic::__dispatch__::functor::update);
    }
  }
}

#endif
