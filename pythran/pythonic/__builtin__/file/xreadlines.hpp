#ifndef PYTHONIC_BUILTIN_FILE_XREADLINES_HPP
#define PYTHONIC_BUILTIN_FILE_XREADLINES_HPP

#include "pythonic/include/__builtin__/file/xreadlines.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      types::file &xreadlines(types::file &f)
      {
        return f;
      }

      types::file &&xreadlines(types::file &&f)
      {
        return std::forward<types::file>(f);
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::file, xreadlines);
    }
  }
}
#endif
