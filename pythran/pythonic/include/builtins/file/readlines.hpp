#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_READLINES_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_READLINES_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      template <class F>
      types::list<types::str> readlines(F &&f);
      template <class F>
      types::list<types::str> readlines(F &&f, long sizehint);

      PROXY_DECL(pythonic::builtins::file, readlines);
    }
  }
}
#endif
