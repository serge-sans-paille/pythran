#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_WRITELINES_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_WRITELINES_HPP

#include "pythonic/include/__builtin__/file/writelines.hpp"

namespace pythonic
{
  namespace io
  {

    namespace _io
    {
      namespace TextIOWrapper {
        USING_FUNCTOR(writelines, __builtin__::file::functor::writelines);
      }
    }
  }

}
#endif
