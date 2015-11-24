#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_CLOSE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_CLOSE_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      void close(types::file &f);
      void close(types::file &&f);

      DECLARE_FUNCTOR(pythonic::__builtin__::file, close);
    }
  }
}
#endif
