#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_FILENO_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_FILENO_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      long fileno(types::file const &f);

      PROXY_DECL(pythonic::builtins::file, fileno);
    }
  }
}
#endif
