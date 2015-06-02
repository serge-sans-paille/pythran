#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_CLOSE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_CLOSE_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      void close(types::file &f);
      void close(types::file &&f);

      PROXY_DECL(pythonic::__builtin__::file, close);
    }
  }
}
#endif
