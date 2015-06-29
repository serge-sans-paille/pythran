#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_ISATTY_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_ISATTY_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      bool isatty(types::file const &f);

      PROXY_DECL(pythonic::builtins::file, isatty);
    }
  }
}
#endif
