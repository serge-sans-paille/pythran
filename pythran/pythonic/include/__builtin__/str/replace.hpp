#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_REPLACE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_REPLACE_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      types::str replace(types::str const &self, types::str const &old_pattern,
                         types::str const &new_pattern,
                         long count = std::numeric_limits<long>::max());

      DECLARE_FUNCTOR(pythonic::__builtin__::str, replace);
    }
  }
}
#endif
