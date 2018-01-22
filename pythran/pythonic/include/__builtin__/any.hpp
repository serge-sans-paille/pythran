#ifndef PYTHONIC_INCLUDE_BUILTIN_ANY_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ANY_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{
  template <class Iterable>
  bool any(Iterable &&s);

  DECLARE_FUNCTOR(pythonic::__builtin__, any);
}
PYTHONIC_NS_END

#endif
