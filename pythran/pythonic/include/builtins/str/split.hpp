#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_SPLIT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_SPLIT_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/none.hpp"
#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace str
    {

      types::list<types::str> split(types::str const &in,
                                    types::str const &sep = " \n",
                                    long maxsplit = -1);

      types::list<types::str>
      split(types::str const &s, types::none_type const &, long maxsplit = -1);

      PROXY_DECL(pythonic::builtins::str, split);
    }
  }
}
#endif
