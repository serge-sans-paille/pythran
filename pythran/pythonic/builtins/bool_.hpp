#ifndef PYTHONIC_BUILTIN_BOOL_HPP
#define PYTHONIC_BUILTIN_BOOL_HPP

#include "pythonic/include/builtins/bool_.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/tuple.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{
  namespace functor
  {

    template <class T>
    bool bool_::operator()(T const &val) const
    {
      return static_cast<bool>(val);
    }

    template <class... Ts>
    bool bool_::operator()(std::tuple<Ts...> const &val) const
    {
      return sizeof...(Ts);
    }

    template <class T, size_t N>
    bool bool_::operator()(types::array<T, N> const &val) const
    {
      return N;
    }

    bool bool_::operator()() const
    {
      return false;
    }
  }
}
PYTHONIC_NS_END

#endif
