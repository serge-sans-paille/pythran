#ifndef PYTHONIC_BUILTIN_FILE_READ_HPP
#define PYTHONIC_BUILTIN_FILE_READ_HPP

#include "pythonic/include/__builtin__/file/read.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
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

    DEFINE_FUNCTOR(pythonic::__builtin__::file, read);
  }
}
PYTHONIC_NS_END
#endif
