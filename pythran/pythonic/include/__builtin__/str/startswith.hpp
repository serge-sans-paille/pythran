#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_STARTSWITH_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_STARTSWITH_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      bool startswith(types::str const &s, types::str const &prefix,
                      long start = 0, long end = -1);

      DECLARE_FUNCTOR(pythonic::__builtin__::str, startswith);
    }
  }
}
#endif
