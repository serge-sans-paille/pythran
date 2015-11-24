#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_ISALPHA_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_ISALPHA_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/str.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      bool isalpha(types::str const &s);

      DECLARE_FUNCTOR(pythonic::__builtin__::str, isalpha);
    }
  }
}
#endif
