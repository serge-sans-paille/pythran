#ifndef PYTHONIC_BUILTIN_FILE_ISATTY_HPP
#define PYTHONIC_BUILTIN_FILE_ISATTY_HPP

#include "pythonic/include/__builtin__/file/isatty.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      bool isatty(types::file const &f)
      {
        return f.isatty();
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::file, isatty);
    }
  }
}
#endif
