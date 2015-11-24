#ifndef PYTHONIC_BUILTIN_STR_UPPER_HPP
#define PYTHONIC_BUILTIN_STR_UPPER_HPP

#include "pythonic/include/__builtin__/str/upper.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      types::str upper(types::str const &s)
      {
        types::str copy = s;
        std::transform(s.begin(), s.end(), copy.begin(), ::toupper);
        return copy;
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::str, upper);
    }
  }
}
#endif
