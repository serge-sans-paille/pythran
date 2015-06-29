#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_TRUNCATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_TRUNCATE_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      void truncate(types::file &f);
      void truncate(types::file &&f);
      void truncate(types::file &f, long size);
      void truncate(types::file &&f, long size);

      PROXY_DECL(pythonic::builtins::file, truncate);
    }
  }
}
#endif
