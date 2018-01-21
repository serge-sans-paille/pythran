#ifndef PYTHONIC_INCLUDE_BUILTIN_HEX_HPP
#define PYTHONIC_INCLUDE_BUILTIN_HEX_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/str.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  template <class T>
  types::str hex(T const &v);

  DECLARE_FUNCTOR(pythonic::__builtin__, hex);
}
PYTHONIC_NS_END

#endif
