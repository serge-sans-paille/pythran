#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_SEEK_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_SEEK_HPP

#include "pythonic/include/__builtin__/file/seek.hpp"

namespace pythonic
{
  namespace io
  {

    namespace _io
    {
      namespace TextIOWrapper {
        USING_FUNCTOR(seek, __builtin__::file::functor::seek);
      }
    }
  }

}
#endif
