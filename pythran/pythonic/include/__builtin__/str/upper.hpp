#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_UPPER_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_UPPER_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      types::str upper(types::str const &s);

      DECLARE_FUNCTOR(pythonic::__builtin__::str, upper);
    }
  }
}
#endif
