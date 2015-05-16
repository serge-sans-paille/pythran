#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_TELL_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_TELL_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      long tell(types::file const &f);

      PROXY_DECL(pythonic::__builtin__::file, tell);
    }
  }
}
#endif
