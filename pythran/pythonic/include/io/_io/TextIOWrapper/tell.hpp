#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_TELL_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_TELL_HPP

#include "pythonic/include/__builtin__/file/tell.hpp"

PYTHONIC_NS_BEGIN
namespace io
{

  namespace _io
  {
    namespace TextIOWrapper
    {
      USING_FUNCTOR(tell, __builtin__::file::functor::tell);
    }
  }
}
PYTHONIC_NS_END
#endif
