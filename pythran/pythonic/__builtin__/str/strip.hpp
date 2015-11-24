#ifndef PYTHONIC_BUILTIN_STR_STRIP_HPP
#define PYTHONIC_BUILTIN_STR_STRIP_HPP

#include "pythonic/include/__builtin__/str/strip.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {
      types::str strip(types::str const &self, types::str const &to_del)
      {
        if (not self)
          return self;
        auto first = self.find_first_not_of(to_del);
        if (first == -1)
          return types::str();
        else
          return types::str(self.begin() + first,
                            self.begin() + self.find_last_not_of(to_del) + 1);
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::str, strip);
    }
  }
}
#endif
