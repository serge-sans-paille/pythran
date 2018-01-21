#ifndef PYTHONIC_FUNCTOOLS_PARTIAL_HPP
#define PYTHONIC_FUNCTOOLS_PARTIAL_HPP

#include "pythonic/include/functools/partial.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/seq.hpp"

#include <utility>

PYTHONIC_NS_BEGIN

namespace functools
{

  namespace details
  {

    template <typename... ClosureTypes>
    task<ClosureTypes...>::task()
        : closure()
    {
    }

    template <typename... ClosureTypes>
    task<ClosureTypes...>::task(ClosureTypes const &... types)
        : closure(types...)
    {
    }

    template <typename... ClosureTypes>
    template <size_t... S, typename... Types>
    auto task<ClosureTypes...>::call(utils::index_sequence<S...>,
                                     Types &&... types) const
        -> decltype(std::get<0>(closure)(std::get<S + 1>(closure)...,
                                         std::forward<Types>(types)...))
    {
      return std::get<0>(closure)(std::get<S + 1>(closure)...,
                                  std::forward<Types>(types)...);
    }

    template <typename... ClosureTypes>
    template <typename... Types>
    auto task<ClosureTypes...>::operator()(Types &&... types) const -> decltype(
        this->call(utils::make_index_sequence<sizeof...(ClosureTypes)-1>(),
                   std::forward<Types>(types)...))
    {
      return call(utils::make_index_sequence<sizeof...(ClosureTypes)-1>(),
                  std::forward<Types>(types)...);
    }
  }

  template <typename... Types>
  // remove references as closure capture the env by copy
  details::task<typename std::remove_cv<
      typename std::remove_reference<Types>::type>::type...>
  partial(Types &&... types)
  {
    return {std::forward<Types>(types)...};
  }

  DEFINE_FUNCTOR(pythonic::functools, partial);
}
PYTHONIC_NS_END

#endif
