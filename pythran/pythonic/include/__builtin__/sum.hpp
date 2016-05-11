#ifndef PYTHONIC_INCLUDE_BUILTIN_SUM_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SUM_HPP

#include "pythonic/include/types/assignable.hpp"
#include "pythonic/include/types/tuple.hpp"
#include "pythonic/include/utils/int_.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <numeric>

namespace pythonic
{

  namespace __builtin__
  {

    namespace details
    {
      template <class Tuple, size_t N>
      struct tuple_sum {
        auto operator()(Tuple const &t)
            -> decltype(std::get<N>(t) + tuple_sum<Tuple, N - 1>()(t));
      };

      template <class Tuple>
      struct tuple_sum<Tuple, 0> {
        auto operator()(Tuple const &t) -> decltype(std::get<0>(t));
      };
    }

    template <class Iterable, class T>
    auto sum(Iterable s, T start) -> decltype(std::accumulate(
        s.begin(), s.end(),
        static_cast<typename assignable<decltype(start + *s.begin())>::type>(
            start)));

    template <class Iterable>
    auto sum(Iterable s) -> decltype(sum(s, 0L));

    template <class... Types>
    auto sum(std::tuple<Types...> const &t) -> decltype(
        details::tuple_sum<std::tuple<Types...>, sizeof...(Types)-1>()(t));

    DECLARE_FUNCTOR(pythonic::__builtin__, sum);
  }
}

#endif
