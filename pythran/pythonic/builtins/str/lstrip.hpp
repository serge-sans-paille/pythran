#ifndef PYTHONIC_BUILTIN_STR_LSTRIP_HPP
#define PYTHONIC_BUILTIN_STR_LSTRIP_HPP

#include "pythonic/include/builtins/str/lstrip.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      types::str lstrip(types::str const &self, types::str const &to_del)
      {
        return {self.begin() + self.find_first_not_of(to_del), self.end()};
      }

      PROXY_IMPL(pythonic::builtins::str, lstrip);
    }
  }
}
#endif
