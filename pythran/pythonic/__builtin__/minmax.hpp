#ifndef PYTHONIC_BUILTIN_MINMAX_HPP
#define PYTHONIC_BUILTIN_MINMAX_HPP

#include "pythonic/include/__builtin__/minmax.hpp"

#include <utility>
#include <algorithm>

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace details
  {
    template <class T0>
    template <typename Op>
    typename minmax<true, T0>::result_type minmax<true, T0>::
    operator()(Op const &op, T0 &&t)
    {
      return *std::max_element(t.begin(), t.end(), op);
    }

    template <class T0>
    template <typename Op>
    typename minmax<false, T0>::result_type minmax<false, T0>::
    operator()(Op const &, T0 const &t)
    {
      return t;
    }

    template <class T0, class T1>
    template <typename Op>
    typename minmax<false, T0, T1>::result_type minmax<false, T0, T1>::
    operator()(Op const &op, T0 const &t0, T1 const &t1)
    {
      return op(t0, t1) ? t1 : t0;
    }

    template <class T0, class... Types>
    template <typename Op>
    typename minmax<false, T0, Types...>::result_type
        minmax<false, T0, Types...>::
        operator()(Op const &op, T0 const &t0, Types const &... values)
    {
      auto t1 = minmax<false, Types...>()(op, values...);
      return op(t0, t1) ? t1 : t0;
    }
  }
}
PYTHONIC_NS_END

#endif
