#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_FLUSH_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_FLUSH_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      void flush(types::file &f);
      void flush(types::file &&f);

      DECLARE_FUNCTOR(pythonic::__builtin__::file, flush);
    }
  }
}
#endif
