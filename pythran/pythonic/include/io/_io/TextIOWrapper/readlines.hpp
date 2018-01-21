#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_READLINES_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_READLINES_HPP

#include "pythonic/include/__builtin__/file/readlines.hpp"

PYTHONIC_NS_BEGIN
namespace io
{

  namespace _io
  {
    namespace TextIOWrapper
    {
      USING_FUNCTOR(readlines, __builtin__::file::functor::readlines);
    }
  }
}
PYTHONIC_NS_END
#endif
