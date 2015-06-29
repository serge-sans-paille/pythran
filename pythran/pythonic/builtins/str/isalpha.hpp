#ifndef PYTHONIC_BUILTIN_STR_ISALPHA_HPP
#define PYTHONIC_BUILTIN_STR_ISALPHA_HPP

#include "pythonic/include/builtins/str/isalpha.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      bool isalpha(types::str const &s)
      {
        return not s.empty() and
               std::all_of(s.begin(), s.end(), (int (*)(int))std::isalpha);
      }

      PROXY_IMPL(pythonic::builtins::str, isalpha)
    }
  }
}
#endif
