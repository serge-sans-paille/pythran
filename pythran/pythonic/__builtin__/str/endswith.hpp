#ifndef PYTHONIC_BUILTIN_STR_ENDSWITH_HPP
#define PYTHONIC_BUILTIN_STR_ENDSWITH_HPP

#include "pythonic/include/__builtin__/str/endswith.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      bool endswith(types::str const &s, types::str const &suffix, long start,
                    long end)
      {
        if (end == -1)
          end = s.size();
        long rstart = end - suffix.size();
        return rstart >= start and
               s.compare(rstart, suffix.size(), suffix) == 0;
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::str, endswith);
    }
  }
}
#endif
