#ifndef PYTHONIC_INCLUDE_ITERTOOLS_PRODUCT_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_PRODUCT_HPP

#include "pythonic/include/utils/iterator.hpp"
#include "pythonic/include/itertools/common.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <iterator>
#include <type_traits>

namespace pythonic
{

  namespace itertools
  {
    namespace details
    {

      // FIXME : should be a combined_iterator_tag
      template <typename... Iters>
      struct product_iterator
          : std::iterator<std::forward_iterator_tag,
                          std::tuple<typename Iters::value_type...>> {

        std::tuple<typename Iters::iterator...> const it_begin;
        std::tuple<typename Iters::iterator...> const it_end;
        std::tuple<typename Iters::iterator...> it;
        bool end;

        product_iterator() = default;
        template <int... I>
        product_iterator(std::tuple<Iters...> &_iters,
                         utils::seq<I...> const &);
        template <int... I>
        product_iterator(npos, std::tuple<Iters...> &_iters,
                         utils::seq<I...> const &);
        std::tuple<typename Iters::value_type...> operator*() const;
        product_iterator &operator++();
        bool operator==(product_iterator const &other) const;
        bool operator!=(product_iterator const &other) const;
        bool operator<(product_iterator const &other) const;

      private:
        template <size_t N>
        void advance(utils::int_<N>);
        void advance(utils::int_<0>);
        template <int... I>
        std::tuple<typename Iters::value_type...>
        get_value(utils::seq<I...> const &) const;
      };

      template <typename... Iters>
      struct product : utils::iterator_reminder<true, Iters...>,
                       product_iterator<Iters...> {

        using value_type = std::tuple<typename Iters::value_type...>;
        using iterator = product_iterator<Iters...>;

        iterator end_iter;

        product() = default;
        product(Iters const &... _iters);

        iterator &begin();
        iterator const &begin() const;
        iterator const &end() const;
      };
    }

    template <typename... Iter>
    details::product<typename std::remove_cv<
        typename std::remove_reference<Iter>::type>::type...>
    product(Iter &&... iters);

    DECLARE_FUNCTOR(pythonic::itertools, product);
  }
}

#endif
