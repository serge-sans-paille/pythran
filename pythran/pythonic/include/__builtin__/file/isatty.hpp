#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_ISATTY_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_ISATTY_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace file
  {

    bool isatty(types::file const &f);

    DECLARE_FUNCTOR(pythonic::__builtin__::file, isatty);
  }
}
PYTHONIC_NS_END
#endif
