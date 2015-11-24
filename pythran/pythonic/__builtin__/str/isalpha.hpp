#ifndef PYTHONIC_BUILTIN_STR_ISALPHA_HPP
#define PYTHONIC_BUILTIN_STR_ISALPHA_HPP

#include "pythonic/include/__builtin__/str/isalpha.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      bool isalpha(types::str const &s)
      {
        return not s.empty() and
               std::all_of(s.begin(), s.end(), (int (*)(int))std::isalpha);
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::str, isalpha)
    }
  }
}
#endif
