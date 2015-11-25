#ifndef PYTHONIC_BUILTIN_FILE_HPP
#define PYTHONIC_BUILTIN_FILE_HPP

#include "pythonic/include/__builtin__/file.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace anonymous
    {
      types::file file(types::str const &filename, types::str const &strmode)
      {
        return {filename, strmode};
      }
    }

    DEFINE_FUNCTOR(pythonic::__builtin__::anonymous, file);
  }
}

#endif
