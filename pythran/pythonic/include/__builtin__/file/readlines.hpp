#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_READLINES_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_READLINES_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      template <class F>
      types::list<types::str> readlines(F &&f);
      template <class F>
      types::list<types::str> readlines(F &&f, long sizehint);

      DECLARE_FUNCTOR(pythonic::__builtin__::file, readlines);
    }
  }
}
#endif
