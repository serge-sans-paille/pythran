#ifndef PYTHONIC_BUILTIN_FILE_FLUSH_HPP
#define PYTHONIC_BUILTIN_FILE_FLUSH_HPP

#include "pythonic/include/builtins/file/flush.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      void flush(types::file &f)
      {
        f.flush();
      }

      void flush(types::file &&f)
      {
        f.flush();
      }

      PROXY_IMPL(pythonic::builtins::file, flush);
    }
  }
}
#endif
