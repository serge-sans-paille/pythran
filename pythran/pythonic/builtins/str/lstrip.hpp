#ifndef PYTHONIC_BUILTIN_STR_LSTRIP_HPP
#define PYTHONIC_BUILTIN_STR_LSTRIP_HPP

#include "pythonic/include/builtins/str/lstrip.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{

  namespace str
  {

    types::str lstrip(types::str const &self, types::str const &to_del)
    {
      return {self.chars().begin() + self.find_first_not_of(to_del),
              self.chars().end()};
    }
  }
}
PYTHONIC_NS_END
#endif
