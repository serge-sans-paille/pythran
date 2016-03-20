#ifndef PYTHONIC_ITERTOOLS_IMAP_HPP
#define PYTHONIC_ITERTOOLS_IMAP_HPP

#include "pythonic/include/itertools/imap.hpp"

#include "pythonic/itertools/common.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/fwd.hpp"
#include "pythonic/utils/int_.hpp"
#include "pythonic/utils/iterator.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/seq.hpp"

#include <iterator>
#include <tuple>
#include <type_traits>

namespace pythonic
{

  namespace itertools
  {
    namespace details
    {

      template <typename Operator, typename... Iters>
      template <int... I>
      imap_iterator<Operator, Iters...>::imap_iterator(
          Operator const &op, std::tuple<Iters...> &_iters, utils::seq<I...>)
          : it(std::get<I>(_iters).begin()...), _op(op)
      {
      }

      template <typename Operator, typename... Iters>
      template <int... I>
      imap_iterator<Operator, Iters...>::imap_iterator(
          npos, Operator const &op, std::tuple<Iters...> &_iters,
          utils::seq<I...>)
          : it(std::get<I>(_iters).end()...), _op(op)
      {
      }

      template <typename Operator, typename... Iters>
      template <int... I>
      typename imap_res<Operator, Iters...>::type
          imap_iterator<Operator, Iters...>::get_value(utils::seq<I...>,
                                                       std::false_type) const
      {
        return _op(*std::get<I>(it)...);
      }

      template <typename Operator, typename... Iters>
      template <int... I>
      typename imap_res<Operator, Iters...>::type
          imap_iterator<Operator, Iters...>::get_value(utils::seq<I...>,
                                                       std::true_type) const
      {
        return types::make_tuple(*std::get<I>(it)...);
      }

      template <typename Operator, typename... Iters>
      typename imap_res<Operator, Iters...>::type
          imap_iterator<Operator, Iters...>::
          operator*() const
      {
        return get_value(typename utils::gens<sizeof...(Iters)>::type{},
                         std::is_same<Operator, types::none_type>());
      }

      template <typename Operator, typename... Iters>
      template <int... I>
      void imap_iterator<Operator, Iters...>::next(utils::seq<I...>)
      {
        utils::fwd(++std::get<I>(it)...);
      }

      template <typename Operator, typename... Iters>
      imap_iterator<Operator, Iters...> &imap_iterator<Operator, Iters...>::
      operator++()
      {
        next(typename utils::gens<sizeof...(Iters)>::type{});
        return *this;
      }

      template <typename Operator, typename... Iters>
      template <size_t I>
      void imap_iterator<Operator, Iters...>::advance(long i, utils::int_<I>)
      {
        std::get<I>(it) += i;
        advance(i, utils::int_<I - 1>());
      }

      template <typename Operator, typename... Iters>
      void imap_iterator<Operator, Iters...>::advance(long i, utils::int_<0>)
      {
        std::get<0>(it) += i;
      }

      template <typename Operator, typename... Iters>
      imap_iterator<Operator, Iters...> &imap_iterator<Operator, Iters...>::
      operator+=(long i)
      {
        advance(i, utils::int_<sizeof...(Iters)-1>());
        return *this;
      }

      template <typename Operator, typename... Iters>
      imap_iterator<Operator, Iters...> imap_iterator<Operator, Iters...>::
      operator+(long i) const
      {
        imap_iterator<Operator, Iters...> other(*this);
        other += i;
        return other;
      }

      template <typename Operator, typename... Iters>
      template <size_t N>
      bool imap_iterator<Operator, Iters...>::equal(
          imap_iterator<Operator, Iters...> const &other, utils::int_<N>) const
      {
        return std::get<N>(other.it) == std::get<N>(it) or
               equal(other, utils::int_<N - 1>());
      }

      template <typename Operator, typename... Iters>
      bool imap_iterator<Operator, Iters...>::equal(
          imap_iterator<Operator, Iters...> const &other, utils::int_<0>) const
      {
        return std::get<0>(other.it) == std::get<0>(it);
      }

      template <typename Operator, typename... Iters>
      bool imap_iterator<Operator, Iters...>::
      operator==(imap_iterator<Operator, Iters...> const &other) const
      {
        return equal(other, utils::int_<sizeof...(Iters)-1>());
      }

      template <typename Operator, typename... Iters>
      bool imap_iterator<Operator, Iters...>::
      operator!=(imap_iterator<Operator, Iters...> const &other) const
      {
        return !(*this == other);
      }

      template <typename Operator, typename... Iters>
      bool imap_iterator<Operator, Iters...>::
      operator<(imap_iterator<Operator, Iters...> const &other) const
      {
        return !(*this == other);
      }

      template <typename Operator, typename... Iters>
      template <size_t N>
      long imap_iterator<Operator, Iters...>::min_len(
          imap_iterator<Operator, Iters...> const &other, utils::int_<N>) const
      {
        return std::min(std::get<N>(it) - std::get<N>(other.it),
                        min_len(other, utils::int_<N - 1>()));
      }

      template <typename Operator, typename... Iters>
      long imap_iterator<Operator, Iters...>::min_len(
          imap_iterator<Operator, Iters...> const &other, utils::int_<0>) const
      {
        return std::get<0>(it) - std::get<0>(other.it);
      }

      template <typename Operator, typename... Iters>
      long imap_iterator<Operator, Iters...>::
      operator-(imap_iterator<Operator, Iters...> const &other) const
      {
        return min_len(other, utils::int_<sizeof...(Iters)-1>());
      }

      template <typename Operator, typename... Iters>
      template <class... Types>
      imap<Operator, Iters...>::imap(Operator const &_op, Types &&... _iters)
          : utils::iterator_reminder<true, Iters...>(
                std::forward<Types>(_iters)...),
            imap_iterator<Operator, Iters...>(
                _op, this->value,
                typename utils::gens<sizeof...(Iters)>::type{}),
            end_iter(npos(), _op, this->value,
                     typename utils::gens<sizeof...(Iters)>::type{})
      {
      }

      template <typename Operator, typename... Iters>
      typename imap<Operator, Iters...>::iterator &
      imap<Operator, Iters...>::begin()
      {
        return *this;
      }

      template <typename Operator, typename... Iters>
      typename imap<Operator, Iters...>::iterator const &
      imap<Operator, Iters...>::begin() const
      {
        return *this;
      }

      template <typename Operator, typename... Iters>
      typename imap<Operator, Iters...>::iterator const &
      imap<Operator, Iters...>::end() const
      {
        return end_iter;
      }
    }

    template <typename Operator, typename... Iter>
    auto imap(Operator &&_op, Iter &&... iters) -> details::imap<
        typename std::remove_cv<
            typename std::remove_reference<Operator>::type>::type,
        typename std::remove_cv<
            typename std::remove_reference<Iter>::type>::type...>
    {
      return {std::forward<Operator>(_op), std::forward<Iter>(iters)...};
    }

    DEFINE_FUNCTOR(pythonic::itertools, imap);
  }
}

#endif
