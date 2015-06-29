#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_TELL_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_TELL_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      long tell(types::file const &f);

      PROXY_DECL(pythonic::builtins::file, tell);
    }
  }
}
#endif
