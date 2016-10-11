#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_FLUSH_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_FLUSH_HPP

#include "pythonic/include/__builtin__/file/flush.hpp"

namespace pythonic
{

  namespace io
  {

    namespace _io
    {
      namespace TextIOWrapper
      {
        USING_FUNCTOR(flush, __builtin__::file::functor::flush);
      }
    }
  }
}
#endif
