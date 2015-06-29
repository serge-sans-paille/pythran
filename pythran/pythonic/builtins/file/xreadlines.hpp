#ifndef PYTHONIC_BUILTIN_FILE_XREADLINES_HPP
#define PYTHONIC_BUILTIN_FILE_XREADLINES_HPP

#include "pythonic/include/builtins/file/xreadlines.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      types::file &xreadlines(types::file &f)
      {
        return f;
      }

      types::file &&xreadlines(types::file &&f)
      {
        return std::forward<types::file>(f);
      }

      PROXY_IMPL(pythonic::builtins::file, xreadlines);
    }
  }
}
#endif
