#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_TELL_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_TELL_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace file
  {

    long tell(types::file const &f);

    DECLARE_FUNCTOR(pythonic::__builtin__::file, tell);
  }
}
PYTHONIC_NS_END
#endif
