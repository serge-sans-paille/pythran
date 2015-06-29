#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_SEEK_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_SEEK_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/file.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      void seek(types::file &f, long offset);
      void seek(types::file &&f, long offset);
      void seek(types::file &f, long offset, long whence);
      void seek(types::file &&f, long offset, long whence);

      PROXY_DECL(pythonic::builtins::file, seek);
    }
  }
}
#endif
