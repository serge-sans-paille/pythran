#ifndef PYTHONIC_BUILTIN_FILE_WRITE_HPP
#define PYTHONIC_BUILTIN_FILE_WRITE_HPP

#include "pythonic/include/builtins/file/write.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      void write(types::file &f, types::str const &str)
      {
        f.write(str);
      }

      void write(types::file &&f, types::str const &str)
      {
        f.write(str);
      }

      PROXY_IMPL(pythonic::builtins::file, write);
    }
  }
}
#endif
