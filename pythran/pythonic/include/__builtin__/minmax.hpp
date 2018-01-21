#ifndef PYTHONIC_INCLUDE_BUILTIN_MINMAX_HPP
#define PYTHONIC_INCLUDE_BUILTIN_MINMAX_HPP

#include <utility>

PYTHONIC_NS_BEGIN

namespace __builtin__
{
  namespace details
  {
    template <bool n, class... Types>
    struct minmax;

    template <class T0>
    struct minmax<true, T0> {
      using result_type =
          typename std::remove_reference<T0>::type::iterator::value_type;
      template <typename Op>
      result_type operator()(Op const &, T0 &&t);
    };

    template <class T0>
    struct minmax<false, T0> {
      using result_type = T0;
      template <typename Op>
      result_type operator()(Op const &, T0 const &t);
    };

    template <class T0, class T1>
    struct minmax<false, T0, T1> {
      using result_type =
          typename std::remove_cv<typename std::remove_reference<
              typename __combined<T0, T1>::type>::type>::type;
      template <typename Op>
      result_type operator()(Op const &, T0 const &t0, T1 const &t1);
    };

    template <class T0, class... Types>
    struct minmax<false, T0, Types...> {
      using result_type = typename minmax<
          false, T0,
          typename minmax<false, Types...>::result_type>::result_type;
      template <typename Op>
      result_type operator()(Op const &, T0 const &t0, Types const &... values);
    };
  }
}
PYTHONIC_NS_END

#endif
