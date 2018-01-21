#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_ISALPHA_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_ISALPHA_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/str.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace str
  {

    bool isalpha(types::str const &s);

    DECLARE_FUNCTOR(pythonic::__builtin__::str, isalpha);
  }
}
PYTHONIC_NS_END
#endif
