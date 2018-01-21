#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_RSTRIP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_RSTRIP_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace str
  {

    types::str rstrip(types::str const &self, types::str const &to_del = " ");

    DECLARE_FUNCTOR(pythonic::__builtin__::str, rstrip);
  }
}
PYTHONIC_NS_END
#endif
