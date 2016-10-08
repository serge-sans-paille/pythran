#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_CLOSE_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_CLOSE_HPP

#include "pythonic/include/__builtin__/file/close.hpp"

namespace pythonic
{

  namespace io
  {

    namespace _io
    {
      namespace TextIOWrapper {
        USING_FUNCTOR(close, __builtin__::file::functor::close);
      }
    }
  }
}
#endif
