#ifndef PYTHONIC_BUILTIN_STR_SPLIT_HPP
#define PYTHONIC_BUILTIN_STR_SPLIT_HPP

#include "pythonic/include/__builtin__/str/split.hpp"

#include "pythonic/__builtin__/str/strip.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace str
    {

      types::list<types::str> split(types::str const &in, types::str const &sep,
                                    long maxsplit)
      {
        types::str s = strip(in);
        types::list<types::str> res(0);
        size_t current = 0;
        size_t next = 0;
        long numsplit = 0;
        while (next != types::str::npos &&
               (numsplit++ < maxsplit || maxsplit == -1)) {
          next = s.find_first_of(sep, current);
          res.push_back(s.substr(current, next - current));
          current = next + 1;
        }
        if (next != types::str::npos) {
          current = next + 1;
          res.push_back(s.substr(current, s.size() - current));
        }
        return res;
      }

      types::list<types::str> split(types::str const &s,
                                    types::none_type const &, long maxsplit)
      {
        return split(s, " ", maxsplit);
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::str, split);
    }
  }
}
#endif
