#ifndef PYTHONIC_BUILTIN_FILE_ISATTY_HPP
#define PYTHONIC_BUILTIN_FILE_ISATTY_HPP

#include "pythonic/include/builtins/file/isatty.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      bool isatty(types::file const &f)
      {
        return f.isatty();
      }

      PROXY_IMPL(pythonic::builtins::file, isatty);
    }
  }
}
#endif
