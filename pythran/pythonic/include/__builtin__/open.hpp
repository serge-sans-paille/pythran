#ifndef PYTHONIC_INCLUDE_BUILTIN_OPEN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_OPEN_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    types::file open(types::str const &filename,
                     types::str const &strmode = "r");

    DECLARE_FUNCTOR(pythonic::__builtin__, open);
  }
}

#endif
