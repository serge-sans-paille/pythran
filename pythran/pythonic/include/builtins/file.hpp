#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace anonymous
    {
      types::file file(types::str const &filename,
                       types::str const &strmode = "r");
    }

    PROXY_DECL(pythonic::builtins::anonymous, file);
  }
}

#endif
