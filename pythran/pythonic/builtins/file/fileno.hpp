#ifndef PYTHONIC_BUILTIN_FILE_FILENO_HPP
#define PYTHONIC_BUILTIN_FILE_FILENO_HPP

#include "pythonic/include/builtins/file/fileno.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      long fileno(types::file const &f)
      {
        return f.fileno();
      }

      PROXY_IMPL(pythonic::builtins::file, fileno);
    }
  }
}
#endif
