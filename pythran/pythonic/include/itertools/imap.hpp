#ifndef PYTHONIC_INCLUDE_ITERTOOLS_IMAP_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_IMAP_HPP

#include "pythonic/include/itertools/common.hpp"
#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/tuple.hpp"
#include "pythonic/include/utils/int_.hpp"
#include "pythonic/include/utils/iterator.hpp"
#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/seq.hpp"

#include <iterator>
#include <tuple>
#include <type_traits>

namespace pythonic
{
  namespace itertools
  {
    namespace details
    {

      template <class Operator, class... Iters>
      struct imap_res {
        using type = decltype(
            std::declval<Operator>()(std::declval<typename std::iterator_traits<
                typename Iters::iterator>::value_type>()...));
      };

      template <class... Iters>
      struct imap_res<types::none_type, Iters...> {
        using type = decltype(
            types::make_tuple(std::declval<typename std::iterator_traits<
                typename Iters::iterator>::value_type>()...));
      };

      template <typename Operator, typename... Iters>
      struct imap_iterator
          : std::iterator<
                typename utils::iterator_min<typename Iters::iterator...>::type,
                typename imap_res<Operator, Iters...>::type> {

        std::tuple<typename Iters::iterator...> it;
        Operator _op;

        imap_iterator() = default;
        template <int... I>
        imap_iterator(Operator const &_op, std::tuple<Iters...> &_iters,
                      utils::seq<I...>);
        template <int... I>
        imap_iterator(npos, Operator const &_op, std::tuple<Iters...> &_iters,
                      utils::seq<I...>);

        typename imap_res<Operator, Iters...>::type operator*() const;
        imap_iterator &operator++();
        imap_iterator &operator+=(long i);
        imap_iterator operator+(long i) const;
        bool operator==(imap_iterator const &other) const;
        bool operator!=(imap_iterator const &other) const;
        bool operator<(imap_iterator const &other) const;
        long operator-(imap_iterator const &other) const;

      private:
        template <size_t N>
        long min_len(imap_iterator<Operator, Iters...> const &other,
                     utils::int_<N>) const;
        long min_len(imap_iterator<Operator, Iters...> const &other,
                     utils::int_<0>) const;

        template <size_t N>
        bool equal(imap_iterator const &other, utils::int_<N>) const;
        bool equal(imap_iterator const &other, utils::int_<0>) const;

        template <size_t I>
        void advance(long i, utils::int_<I>);
        void advance(long i, utils::int_<0>);

        template <int... I>
        void next(utils::seq<I...>);

        template <int... I>
        typename imap_res<Operator, Iters...>::type
            get_value(utils::seq<I...>, std::true_type) const;
        template <int... I>
        typename imap_res<Operator, Iters...>::type
            get_value(utils::seq<I...>, std::false_type) const;
      };

      template <typename Operator, typename... Iters>
      struct imap : utils::iterator_reminder<true, Iters...>,
                    imap_iterator<Operator, Iters...> {
        using value_type = typename imap_res<Operator, Iters...>::type;
        using iterator = imap_iterator<Operator, Iters...>;

        iterator end_iter;

        imap() = default;
        // Use an extra template to enable forwarding
        template <class... Types>
        imap(Operator const &_op, Types &&... _iters);

        iterator &begin();
        iterator const &begin() const;
        iterator const &end() const;
      };
    }

    template <typename Operator, typename... Iter>
    auto imap(Operator &&_op, Iter &&... iters) -> details::imap<
        typename std::remove_cv<
            typename std::remove_reference<Operator>::type>::type,
        typename std::remove_cv<
            typename std::remove_reference<Iter>::type>::type...>;

    DECLARE_FUNCTOR(pythonic::itertools, imap);
  }

  namespace types
  {

    template <class Op, class Iter>
    struct len_of<pythonic::itertools::details::imap<Op, Iter>> {
      static constexpr long value = len_of<typename std::remove_cv<
          typename std::remove_reference<Iter>::type>::type>::value;
    };

    template <class Op, class I0, class I1, class... Iter>
    struct len_of<pythonic::itertools::details::imap<Op, I0, I1, Iter...>> {
      static constexpr long _head = len_of<typename std::remove_cv<
          typename std::remove_reference<I0>::type>::type>::value;
      static constexpr long _tail =
          len_of<pythonic::itertools::details::imap<Op, I1, Iter...>>::value;
      // take the minimal value. If one is negative, it will be automatically
      // selected
      static constexpr long value = (_head < _tail ? _head : _tail);
    };
  }
}

#endif
