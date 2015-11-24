#ifndef PYTHONIC_INCLUDE_BUILTIN_ANY_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ANY_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {
    template <class Iterable>
    bool any(Iterable &&s);

    DECLARE_FUNCTOR(pythonic::__builtin__, any);
  }
}

#endif
