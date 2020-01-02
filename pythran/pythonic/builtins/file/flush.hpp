#ifndef PYTHONIC_BUILTIN_FILE_FLUSH_HPP
#define PYTHONIC_BUILTIN_FILE_FLUSH_HPP

#include "pythonic/include/builtins/file/flush.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{

  namespace file
  {

    void flush(types::file &f)
    {
      f.flush();
    }

    void flush(types::file &&f)
    {
      f.flush();
    }
  }
}
PYTHONIC_NS_END
#endif
