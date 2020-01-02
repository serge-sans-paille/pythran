#ifndef PYTHONIC_BUILTIN_FILE_READ_HPP
#define PYTHONIC_BUILTIN_FILE_READ_HPP

#include "pythonic/include/builtins/file/read.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{

  namespace file
  {

    types::str read(types::file &f, long size)
    {
      return f.read(size);
    }
    types::str read(types::file &&f, long size)
    {
      return f.read(size);
    }
  }
}
PYTHONIC_NS_END
#endif
