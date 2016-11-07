#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_WRITE_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_WRITE_HPP

#include "pythonic/include/__builtin__/file/write.hpp"

namespace pythonic
{
  namespace io
  {

    namespace _io
    {
      namespace TextIOWrapper
      {
        USING_FUNCTOR(write, __builtin__::file::functor::write);
      }
    }
  }
}
#endif
