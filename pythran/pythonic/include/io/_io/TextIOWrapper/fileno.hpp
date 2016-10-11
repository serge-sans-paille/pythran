#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_FILENO_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_FILENO_HPP

#include "pythonic/include/__builtin__/file/fileno.hpp"

namespace pythonic
{

  namespace io
  {

    namespace _io
    {
      namespace TextIOWrapper
      {
        USING_FUNCTOR(fileno, __builtin__::file::functor::fileno);
      }
    }
  }
}
#endif
