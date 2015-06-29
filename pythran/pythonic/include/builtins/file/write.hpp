#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_WRITE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_WRITE_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      void write(types::file &f, types::str const &str);
      void write(types::file &&f, types::str const &str);

      PROXY_DECL(pythonic::builtins::file, write);
    }
  }
}
#endif
