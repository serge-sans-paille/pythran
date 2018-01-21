#ifndef PYTHONIC_BUILTIN_CHR_HPP
#define PYTHONIC_BUILTIN_CHR_HPP

#include "pythonic/include/__builtin__/chr.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{
  template <class T>
  types::str chr(T const &v)
  {
    return {(char)v};
  }

  DEFINE_FUNCTOR(pythonic::__builtin__, chr);
}
PYTHONIC_NS_END

#endif
