#ifndef PYTHONIC_BUILTIN_STR_RSTRIP_HPP
#define PYTHONIC_BUILTIN_STR_RSTRIP_HPP

#include "pythonic/include/builtins/str/rstrip.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      types::str rstrip(types::str const &self, types::str const &to_del)
      {
        return {self.begin(), self.begin() + self.find_last_not_of(to_del) + 1};
      }

      PROXY_IMPL(pythonic::builtins::str, rstrip);
    }
  }
}
#endif
