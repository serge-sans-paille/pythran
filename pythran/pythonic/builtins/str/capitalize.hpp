#ifndef PYTHONIC_BUILTIN_STR_CAPITALIZE_HPP
#define PYTHONIC_BUILTIN_STR_CAPITALIZE_HPP

#include "pythonic/include/builtins/str/capitalize.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      types::str capitalize(types::str const &s)
      {
        if (s.empty())
          return s;
        else {
          types::str copy = s;
          copy[0] = ::toupper(s[0]);
          std::transform(s.begin() + 1, s.end(), copy.begin() + 1, ::tolower);
          return copy;
        }
      }

      PROXY_IMPL(pythonic::builtins::str, capitalize);
    }
  }
}
#endif
