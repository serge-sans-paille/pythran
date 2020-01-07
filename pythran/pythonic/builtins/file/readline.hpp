#ifndef PYTHONIC_BUILTIN_FILE_READLINE_HPP
#define PYTHONIC_BUILTIN_FILE_READLINE_HPP

#include "pythonic/include/builtins/file/readline.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{

  namespace file
  {

    types::str readline(types::file &f, long size)
    {
      return size < 0 ? f.readline() : f.readline(size);
    }

    types::str readline(types::file &&f, long size)
    {
      return size < 0 ? f.readline() : f.readline(size);
    }
  }
}
PYTHONIC_NS_END
#endif
