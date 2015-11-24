#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_ISDIGIT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_ISDIGIT_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      bool isdigit(types::str const &s);

      DECLARE_FUNCTOR(pythonic::__builtin__::str, isdigit);
    }
  }
}
#endif
