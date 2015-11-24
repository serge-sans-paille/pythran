#ifndef PYTHONIC_BUILTIN_STR_LOWER_HPP
#define PYTHONIC_BUILTIN_STR_LOWER_HPP

#include "pythonic/include/__builtin__/str/lower.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      types::str lower(types::str const &s)
      {
        types::str copy = s;
        std::transform(s.begin(), s.end(), copy.begin(), ::tolower);
        return copy;
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::str, lower);
    }
  }
}
#endif
