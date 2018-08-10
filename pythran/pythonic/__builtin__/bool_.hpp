#ifndef PYTHONIC_BUILTIN_BOOL_HPP
#define PYTHONIC_BUILTIN_BOOL_HPP

#include "pythonic/include/__builtin__/bool_.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{
  namespace functor
  {

    template <class T>
    bool bool_::operator()(T &&val) const
    {
      return static_cast<bool>(val);
    }

    bool bool_::operator()() const
    {
      return false;
    }
  }
}
PYTHONIC_NS_END

#endif
