#ifndef PYTHONIC_BUILTIN_STR_UPPER_HPP
#define PYTHONIC_BUILTIN_STR_UPPER_HPP

#include "pythonic/include/__builtin__/str/upper.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace str
  {

    types::str upper(types::str const &s)
    {
      types::str copy = s;
      std::transform(s.chars().begin(), s.chars().end(), copy.chars().begin(),
                     ::toupper);
      return copy;
    }
  }
}
PYTHONIC_NS_END
#endif
