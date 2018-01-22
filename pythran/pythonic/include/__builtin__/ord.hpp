#ifndef PYTHONIC_INCLUDE_BUILTIN_ORD_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ORD_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{
  long ord(types::str const &v);

  long ord(char v);

  DECLARE_FUNCTOR(pythonic::__builtin__, ord);
}
PYTHONIC_NS_END

#endif
