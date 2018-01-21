#ifndef PYTHONIC_BUILTIN_FILE_FLUSH_HPP
#define PYTHONIC_BUILTIN_FILE_FLUSH_HPP

#include "pythonic/include/__builtin__/file/flush.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
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

    DEFINE_FUNCTOR(pythonic::__builtin__::file, flush);
  }
}
PYTHONIC_NS_END
#endif
