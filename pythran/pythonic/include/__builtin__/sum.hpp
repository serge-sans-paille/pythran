#ifndef PYTHONIC_INCLUDE_BUILTIN_SUM_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SUM_HPP

#include "pythonic/include/types/assignable.hpp"
#include "pythonic/include/types/tuple.hpp"
#include "pythonic/include/utils/int_.hpp"
#include "pythonic/include/utils/proxy.hpp"

#include <algorithm>

namespace pythonic
{

  namespace __builtin__
  {

    namespace details
    {
      template <class Tuple>
      auto tuple_sum(Tuple const &t, utils::int_<0>)
          -> decltype(std::get<0>(t));

      // FIXME : Why do we need this? compiler doesn't succeed without it...
      template <class Tuple>
      auto tuple_sum(Tuple const &t, utils::int_<1>)
          -> decltype(std::get<0>(t) + std::get<1>(t));

      template <class Tuple, size_t I>
      auto tuple_sum(Tuple const &t, utils::int_<I>)
          -> decltype(std::get<I>(t) + tuple_sum(t, utils::int_<I - 1>()));
    }

    template <class Iterable, class T>
    auto sum(Iterable s, T start) -> decltype(std::accumulate(
        s.begin(), s.end(),
        static_cast<typename assignable<decltype(start + *s.begin())>::type>(
            start)));

    template <class Iterable>
    auto sum(Iterable s) -> decltype(sum(s, 0L));

    template <class... Types>
    auto sum(std::tuple<Types...> const &t)
        -> decltype(details::tuple_sum(t, utils::int_<sizeof...(Types)-1>()));

    PROXY_DECL(pythonic::__builtin__, sum);
  }
}

#endif
