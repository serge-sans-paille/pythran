#ifndef PYTHONIC_BUILTIN_FILE_TELL_HPP
#define PYTHONIC_BUILTIN_FILE_TELL_HPP

#include "pythonic/include/__builtin__/file/tell.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

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
PYTHONIC_NS_END
#endif
