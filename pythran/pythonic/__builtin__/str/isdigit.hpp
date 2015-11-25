#ifndef PYTHONIC_BUILTIN_STR_ISDIGIT_HPP
#define PYTHONIC_BUILTIN_STR_ISDIGIT_HPP

#include "pythonic/include/__builtin__/str/isdigit.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      bool isdigit(types::str const &s)
      {
        return not s.empty() and
               std::all_of(s.begin(), s.end(), (int (*)(int))std::isdigit);
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::str, isdigit);
    }
  }
}
#endif
