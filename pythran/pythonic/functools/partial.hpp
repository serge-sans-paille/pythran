#ifndef PYTHONIC_FUNCTOOLS_PARTIAL_HPP
#define PYTHONIC_FUNCTOOLS_PARTIAL_HPP

#include "pythonic/include/functools/partial.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/seq.hpp"

#include <utility>

namespace pythonic
{

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
      template <int... S, typename... Types>
      auto task<ClosureTypes...>::call(utils::seq<S...>,
                                       Types &&... types) const
          -> decltype(std::get<0>(closure)(std::get<S + 1>(closure)...,
                                           std::forward<Types>(types)...))
      {
        return std::get<0>(closure)(std::get<S + 1>(closure)...,
                                    std::forward<Types>(types)...);
      }

      template <typename... ClosureTypes>
      template <typename... Types>
      auto task<ClosureTypes...>::operator()(Types &&... types) const
          -> decltype(this->call(
              typename utils::gens<sizeof...(ClosureTypes)-1>::type(),
              std::forward<Types>(types)...))
      {
        return call(typename utils::gens<sizeof...(ClosureTypes)-1>::type(),
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
}

#endif
