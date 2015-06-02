#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_WRITE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_WRITE_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      void write(types::file &f, types::str const &str);
      void write(types::file &&f, types::str const &str);

      PROXY_DECL(pythonic::__builtin__::file, write);
    }
  }
}
#endif
