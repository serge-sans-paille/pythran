#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_READ_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_READ_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      types::str read(types::file &f, long size = -1);
      types::str read(types::file &&f, long size = -1);

      DECLARE_FUNCTOR(pythonic::__builtin__::file, read);
    }
  }
}
#endif
