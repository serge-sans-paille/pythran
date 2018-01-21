#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_FILENO_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_FILENO_HPP

#include "pythonic/include/__builtin__/file/fileno.hpp"

PYTHONIC_NS_BEGIN

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
PYTHONIC_NS_END
#endif
