#ifndef PYTHONIC_BUILTIN_FILE_READLINES_HPP
#define PYTHONIC_BUILTIN_FILE_READLINES_HPP

#include "pythonic/include/__builtin__/file/readlines.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      template <class F>
      types::list<types::str> readlines(F &&f)
      {
        return f.readlines();
      }

      template <class F>
      types::list<types::str> readlines(F &&f, long sizehint)
      {
        return f.readlines(sizehint);
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::file, readlines);
    }
  }
}
#endif
