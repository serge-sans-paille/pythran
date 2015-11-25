#ifndef PYTHONIC_BUILTIN_STR_FIND_HPP
#define PYTHONIC_BUILTIN_STR_FIND_HPP

#include "pythonic/include/__builtin__/str/find.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      long find(types::str const &s, types::str const &value, long start,
                long end)
      {
        if (end < 0)
          end += s.size();
        long a = s.find(value, start);
        return (a > end) ? -1 : a;
      }

      long find(types::str const &s, types::str const &value, long start)
      {
        return find(s, value, start, s.size());
      }

      long find(types::str const &s, types::str const &value)
      {
        return find(s, value, 0, s.size());
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::str, find);
    }
  }
}
#endif
