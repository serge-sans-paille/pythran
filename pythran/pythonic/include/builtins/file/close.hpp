#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_CLOSE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_CLOSE_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      void close(types::file &f);
      void close(types::file &&f);

      PROXY_DECL(pythonic::builtins::file, close);
    }
  }
}
#endif
