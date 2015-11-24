#ifndef PYTHONIC_BUILTIN_STR_RSTRIP_HPP
#define PYTHONIC_BUILTIN_STR_RSTRIP_HPP

#include "pythonic/include/__builtin__/str/rstrip.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      types::str rstrip(types::str const &self, types::str const &to_del)
      {
        return {self.begin(), self.begin() + self.find_last_not_of(to_del) + 1};
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::str, rstrip);
    }
  }
}
#endif
