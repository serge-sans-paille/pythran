#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_NEXT_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_NEXT_HPP

#include "pythonic/include/__builtin__/file/next.hpp"

PYTHONIC_NS_BEGIN
namespace io
{

  namespace _io
  {
    namespace TextIOWrapper
    {
      USING_FUNCTOR(next, __builtin__::file::functor::next);
    }
  }
}
PYTHONIC_NS_END
#endif
