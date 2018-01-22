#ifndef PYTHONIC_BUILTIN_FILE_CLOSE_HPP
#define PYTHONIC_BUILTIN_FILE_CLOSE_HPP

#include "pythonic/include/__builtin__/file/close.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
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

    DEFINE_FUNCTOR(pythonic::__builtin__::file, close);
  }
}
PYTHONIC_NS_END
#endif
