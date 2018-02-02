#ifndef PYTHONIC_BUILTIN_INT_HPP
#define PYTHONIC_BUILTIN_INT_HPP

#include "pythonic/include/__builtin__/int_.hpp"

#include "pythonic/types/str.hpp"

#include <cassert>

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace functor
  {
    int_::type int_::operator()(char const t[], int base) const
    {
      return std::strtol(t, nullptr, base);
    }
    int_::type int_::operator()(types::str const &t, int base) const
    {
      return (*this)(t.c_str(), base);
    }

    template <class T>
    int_::type int_::operator()(T &&t) const
    {
      return t;
    }

    int_::type int_::operator()(char t) const
    {
      assert(t >= '0' && t <= '9');
      return t - '0';
    }

    int_::type int_::operator()() const
    {
      return 0L;
    }
  }
}
PYTHONIC_NS_END

#endif
