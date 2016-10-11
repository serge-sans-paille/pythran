#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_XREADLINES_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_XREADLINES_HPP

#include "pythonic/include/__builtin__/file/xreadlines.hpp"

namespace pythonic
{
  namespace io
  {

    namespace _io
    {
      namespace TextIOWrapper
      {
        USING_FUNCTOR(xreadlines, __builtin__::file::functor::xreadlines);
      }
    }
  }
}
#endif
