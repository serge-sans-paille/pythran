#ifndef PYTHONIC_BUILTIN_STR_UPPER_HPP
#define PYTHONIC_BUILTIN_STR_UPPER_HPP

#include "pythonic/include/builtins/str/upper.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      types::str upper(types::str const &s)
      {
        types::str copy = s;
        std::transform(s.begin(), s.end(), copy.begin(), ::toupper);
        return copy;
      }

      PROXY_IMPL(pythonic::builtins::str, upper);
    }
  }
}
#endif
