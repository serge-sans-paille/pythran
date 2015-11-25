#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_ENDSWITH_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_ENDSWITH_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      // TODO : Add implementation for tuple as first argument.
      bool endswith(types::str const &s, types::str const &suffix,
                    long start = 0, long end = -1);

      DECLARE_FUNCTOR(pythonic::__builtin__::str, endswith);
    }
  }
}
#endif
