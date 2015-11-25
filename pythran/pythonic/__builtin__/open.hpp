#ifndef PYTHONIC_BUILTIN_OPEN_HPP
#define PYTHONIC_BUILTIN_OPEN_HPP

#include "pythonic/include/__builtin__/open.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    types::file open(types::str const &filename, types::str const &strmode)
    {
      return {filename, strmode};
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, open);
  }
}

#endif
