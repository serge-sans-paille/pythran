#ifndef PYTHONIC_BUILTIN_FILE_TELL_HPP
#define PYTHONIC_BUILTIN_FILE_TELL_HPP

#include "pythonic/include/__builtin__/file/tell.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      long tell(types::file const &f)
      {
        return f.tell();
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::file, tell);
    }
  }
}
#endif
