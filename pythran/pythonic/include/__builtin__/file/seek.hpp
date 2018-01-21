#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_SEEK_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_SEEK_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/file.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace file
  {

    void seek(types::file &f, long offset);
    void seek(types::file &&f, long offset);
    void seek(types::file &f, long offset, long whence);
    void seek(types::file &&f, long offset, long whence);

    DECLARE_FUNCTOR(pythonic::__builtin__::file, seek);
  }
}
PYTHONIC_NS_END
#endif
