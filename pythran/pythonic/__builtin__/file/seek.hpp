#ifndef PYTHONIC_BUILTIN_FILE_SEEK_HPP
#define PYTHONIC_BUILTIN_FILE_SEEK_HPP

#include "pythonic/include/__builtin__/file/seek.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      void seek(types::file &f, long offset)
      {
        f.seek(offset);
      }

      void seek(types::file &&f, long offset)
      {
        // Nothing have to be done as it is a lvalue
      }

      void seek(types::file &f, long offset, long whence)
      {
        f.seek(offset, whence);
      }

      void seek(types::file &&f, long offset, long whence)
      {
        // Nothing have to be done as it is a lvalue
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::file, seek);
    }
  }
}
#endif
