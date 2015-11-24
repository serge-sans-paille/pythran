#ifndef PYTHONIC_BUILTIN_MAX_HPP
#define PYTHONIC_BUILTIN_MAX_HPP

#include "pythonic/include/__builtin__/max.hpp"

#include "pythonic/utils/functor.hpp"

#include <utility>
#include <algorithm>

namespace pythonic
{

  namespace __builtin__
  {

    namespace details
    {
      template <class T0>
      typename max<true, T0>::result_type max<true, T0>::operator()(T0 &&t)
      {
        return *std::max_element(t.begin(), t.end());
      }

      template <class T0>
      typename max<false, T0>::result_type max<false, T0>::
      operator()(T0 const &t)
      {
        return t;
      }

      template <class T0, class T1>
      typename max<false, T0, T1>::result_type max<false, T0, T1>::
      operator()(T0 const &t0, T1 const &t1)
      {
        return t0 > t1 ? t0 : t1;
      }

      template <class T0, class... Types>
      typename max<false, T0, Types...>::result_type max<false, T0, Types...>::
      operator()(T0 const &t0, Types const &... values)
      {
        auto t1 = max<false, Types...>()(values...);
        return t0 > t1 ? t0 : t1;
      }
    }

    template <class... Types>
    typename details::max<sizeof...(Types) == 1, Types...>::result_type
    max(Types &&... values)
    {
      return details::max<sizeof...(Types) == 1, Types...>()(
          std::forward<Types>(values)...);
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, max);
  }
}

#endif
