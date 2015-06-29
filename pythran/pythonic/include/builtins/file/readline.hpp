#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_READLINE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_READLINE_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      types::str readline(types::file &f, long size = -1);
      types::str readline(types::file &&f, long size = -1);

      PROXY_DECL(pythonic::builtins::file, readline);
    }
  }
}
#endif
