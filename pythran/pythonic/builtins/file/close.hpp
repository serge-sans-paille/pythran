#ifndef PYTHONIC_BUILTIN_FILE_CLOSE_HPP
#define PYTHONIC_BUILTIN_FILE_CLOSE_HPP

#include "pythonic/include/builtins/file/close.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{

  namespace file
  {

    void close(types::file &f)
    {
      f.close();
    }

    void close(types::file &&f)
    {
      f.close();
    }
  }
}
PYTHONIC_NS_END
#endif
