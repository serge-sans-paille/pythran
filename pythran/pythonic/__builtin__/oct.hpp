#ifndef PYTHONIC_BUILTIN_OCT_HPP
#define PYTHONIC_BUILTIN_OCT_HPP

#include "pythonic/include/__builtin__/oct.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

#include <sstream>

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  template <class T>
  types::str oct(T const &v)
  {
    std::ostringstream oss;
    oss <<
#if defined(__PYTHRAN__) && __PYTHRAN__ == 3
        "0o"
#else
        '0'
#endif
        << std::oct << v;
    return oss.str();
  }

  DEFINE_FUNCTOR(pythonic::__builtin__, oct);
}
PYTHONIC_NS_END

#endif
