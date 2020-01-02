#ifndef PYTHONIC_BUILTIN_FILE_TRUNCATE_HPP
#define PYTHONIC_BUILTIN_FILE_TRUNCATE_HPP

#include "pythonic/include/builtins/file/truncate.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{

  namespace file
  {

    void truncate(types::file &f)
    {
      f.truncate();
    }

    void truncate(types::file &&f)
    {
      f.truncate();
    }

    void truncate(types::file &f, long size)
    {
      f.truncate(size);
    }

    void truncate(types::file &&f, long size)
    {
      f.truncate(size);
    }
  }
}
PYTHONIC_NS_END
#endif
