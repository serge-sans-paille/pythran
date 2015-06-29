#ifndef PYTHONIC_BUILTIN_STR_ENDSWITH_HPP
#define PYTHONIC_BUILTIN_STR_ENDSWITH_HPP

#include "pythonic/include/builtins/str/endswith.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
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

      PROXY_IMPL(pythonic::builtins::str, endswith);
    }
  }
}
#endif
