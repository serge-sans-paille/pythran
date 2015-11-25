#ifndef PYTHONIC_BUILTIN_SUM_HPP
#define PYTHONIC_BUILTIN_SUM_HPP

#include "pythonic/include/__builtin__/sum.hpp"

#include "pythonic/types/assignable.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/int_.hpp"
#include "pythonic/utils/functor.hpp"

#include <algorithm>

namespace pythonic
{

  namespace __builtin__
  {

    namespace details
    {
      template <class Tuple, size_t N>
      auto tuple_sum<Tuple, N>::operator()(Tuple const &t)
          -> decltype(std::get<N>(t) + tuple_sum<Tuple, N - 1>()(t))
      {
        return std::get<N>(t) + tuple_sum<Tuple, N - 1>()(t);
      }

      template <class Tuple>
      auto tuple_sum<Tuple, 0>::operator()(Tuple const &t)
          -> decltype(std::get<0>(t))
      {
        return std::get<0>(t);
      }
    }

    template <class Iterable, class T>
    auto sum(Iterable s, T start) -> decltype(std::accumulate(
        s.begin(), s.end(),
        static_cast<typename assignable<decltype(start + *s.begin())>::type>(
            start)))
    {
      return std::accumulate(
          s.begin(), s.end(),
          static_cast<typename assignable<decltype(start + *s.begin())>::type>(
              start));
    }

    template <class Iterable>
    auto sum(Iterable s) -> decltype(sum(s, 0L))
    {
      return sum(s, 0L);
    }

    template <class... Types>
    auto sum(std::tuple<Types...> const &t) -> decltype(
        details::tuple_sum<std::tuple<Types...>, sizeof...(Types)-1>()(t))
    {
      return details::tuple_sum<std::tuple<Types...>, sizeof...(Types)-1>()(t);
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, sum);
  }
}

#endif
