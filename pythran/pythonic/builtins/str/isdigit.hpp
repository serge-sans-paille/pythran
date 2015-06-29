#ifndef PYTHONIC_BUILTIN_STR_ISDIGIT_HPP
#define PYTHONIC_BUILTIN_STR_ISDIGIT_HPP

#include "pythonic/include/builtins/str/isdigit.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      bool isdigit(types::str const &s)
      {
        return not s.empty() and
               std::all_of(s.begin(), s.end(), (int (*)(int))std::isdigit);
      }

      PROXY_IMPL(pythonic::builtins::str, isdigit);
    }
  }
}
#endif
