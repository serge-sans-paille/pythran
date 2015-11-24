#ifndef PYTHONIC_BUILTIN_STR_LSTRIP_HPP
#define PYTHONIC_BUILTIN_STR_LSTRIP_HPP

#include "pythonic/include/__builtin__/str/lstrip.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      types::str lstrip(types::str const &self, types::str const &to_del)
      {
        return {self.begin() + self.find_first_not_of(to_del), self.end()};
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::str, lstrip);
    }
  }
}
#endif
