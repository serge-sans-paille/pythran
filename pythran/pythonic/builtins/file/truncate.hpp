#ifndef PYTHONIC_BUILTIN_FILE_TRUNCATE_HPP
#define PYTHONIC_BUILTIN_FILE_TRUNCATE_HPP

#include "pythonic/include/builtins/file/truncate.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      void truncate(types::file &f)
      {
        f.truncate();
      }

      void truncate(types::file &&f)
      {
        f.truncate();
      }

      void truncate(types::file &f, long size)
      {
        f.truncate(size);
      }

      void truncate(types::file &&f, long size)
      {
        f.truncate(size);
      }

      PROXY_IMPL(pythonic::builtins::file, truncate);
    }
  }
}
#endif
