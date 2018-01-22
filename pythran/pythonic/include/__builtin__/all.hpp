#ifndef PYTHONIC_INCLUDE_BUILTIN_ALL_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ALL_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  template <class Iterable>
  bool all(Iterable &&s);

  DECLARE_FUNCTOR(pythonic::__builtin__, all);
}
PYTHONIC_NS_END

#endif
