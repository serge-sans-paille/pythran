#ifndef PYTHONIC_INCLUDE_BUILTIN_BIN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_BIN_HPP

#include "pythonic/include/utils/functor.hpp"

#include "pythonic/include/types/str.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{
  template <class T>
  types::str bin(T const &v);

  DEFINE_FUNCTOR(pythonic::builtins, bin);
}
PYTHONIC_NS_END

#endif
