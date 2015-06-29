#ifndef PYTHONIC_BUILTIN_STR_LOWER_HPP
#define PYTHONIC_BUILTIN_STR_LOWER_HPP

#include "pythonic/include/builtins/str/lower.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      types::str lower(types::str const &s)
      {
        types::str copy = s;
        std::transform(s.begin(), s.end(), copy.begin(), ::tolower);
        return copy;
      }

      PROXY_IMPL(pythonic::builtins::str, lower);
    }
  }
}
#endif
