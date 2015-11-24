#ifndef PYTHONIC_BUILTIN_FILE_TRUNCATE_HPP
#define PYTHONIC_BUILTIN_FILE_TRUNCATE_HPP

#include "pythonic/include/__builtin__/file/truncate.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
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

      DEFINE_FUNCTOR(pythonic::__builtin__::file, truncate);
    }
  }
}
#endif
