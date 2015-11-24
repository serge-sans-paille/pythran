#ifndef PYTHONIC_INCLUDE_BUILTIN_MIN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_MIN_HPP

#include "pythonic/include/utils/functor.hpp"

#include <utility>

namespace pythonic
{

  namespace __builtin__
  {
    namespace details
    {
      template <int n, class... Types>
      struct min;

      template <class T0>
      struct min<true, T0> {
        using result_type =
            typename std::remove_reference<T0>::type::iterator::value_type;
        result_type operator()(T0 &&t);
      };

      template <class T0>
      struct min<false, T0> {
        using result_type = T0;
        result_type operator()(T0 const &t);
      };

      template <class T0, class T1>
      struct min<false, T0, T1> {
        using result_type = typename __combined<T0, T1>::type;
        result_type operator()(T0 const &t0, T1 const &t1);
      };

      template <class T0, class... Types>
      struct min<false, T0, Types...> {
        using result_type = typename min<
            false, T0, typename min<false, Types...>::result_type>::result_type;
        result_type operator()(T0 const &t0, Types const &... values);
      };
    }

    template <class... Types>
    typename details::min<sizeof...(Types) == 1, Types...>::result_type
    min(Types &&... values);

    DECLARE_FUNCTOR(pythonic::__builtin__, min);
  }
}

#endif
