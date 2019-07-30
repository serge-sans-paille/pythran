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
    int_::type int_::operator()(char const t[], long base) const
    {
      return std::strtol(t, nullptr, base);
    }
    int_::type int_::operator()(types::str const &t, long base) const
    {
      return (*this)(t.c_str(), base);
    }

    template <class T>
    int_::type int_::operator()(T &&t) const
    {
      return static_cast<int_::type>(t);
    }

    int_::type int_::operator()() const
    {
      return 0L;
    }
  }
}
PYTHONIC_NS_END

#endif
