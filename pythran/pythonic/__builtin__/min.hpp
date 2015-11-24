#ifndef PYTHONIC_BUILTIN_MIN_HPP
#define PYTHONIC_BUILTIN_MIN_HPP

#include "pythonic/include/__builtin__/min.hpp"

#include "pythonic/utils/functor.hpp"

#include <algorithm>
#include <utility>

namespace pythonic
{

  namespace __builtin__
  {

    namespace details
    {
      template <class T0>
      typename min<true, T0>::result_type min<true, T0>::operator()(T0 &&t)
      {
        return *std::min_element(t.begin(), t.end());
      }

      template <class T0>
      typename min<false, T0>::result_type min<false, T0>::
      operator()(T0 const &t)
      {
        return t;
      }

      template <class T0, class T1>
      typename min<false, T0, T1>::result_type min<false, T0, T1>::
      operator()(T0 const &t0, T1 const &t1)
      {
        return t0 < t1 ? t0 : t1;
      }

      template <class T0, class... Types>
      typename min<false, T0, Types...>::result_type min<false, T0, Types...>::
      operator()(T0 const &t0, Types const &... values)
      {
        auto t1 = min<false, Types...>()(values...);
        return t0 < t1 ? t0 : t1;
      }
    }

    template <class... Types>
    typename details::min<sizeof...(Types) == 1, Types...>::result_type
    min(Types &&... values)
    {
      return details::min<sizeof...(Types) == 1, Types...>()(
          std::forward<Types>(values)...);
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, min);
  }
}

#endif
