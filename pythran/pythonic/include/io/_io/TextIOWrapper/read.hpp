#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_READ_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_READ_HPP

#include "pythonic/include/__builtin__/file/read.hpp"

PYTHONIC_NS_BEGIN
namespace io
{

  namespace _io
  {
    namespace TextIOWrapper
    {
      USING_FUNCTOR(read, __builtin__::file::functor::read);
    }
  }
}
PYTHONIC_NS_END
#endif
