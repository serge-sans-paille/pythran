#ifndef PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_TRUNCATE_HPP
#define PYTHONIC_INCLUDE_IO__IO_TEXTIOWRAPPER_TRUNCATE_HPP

#include "pythonic/include/__builtin__/file/truncate.hpp"

PYTHONIC_NS_BEGIN
namespace io
{

  namespace _io
  {
    namespace TextIOWrapper
    {
      USING_FUNCTOR(truncate, __builtin__::file::functor::truncate);
    }
  }
}
PYTHONIC_NS_END
#endif
