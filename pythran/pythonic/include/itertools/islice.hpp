#ifndef PYTHONIC_INCLUDE_ITERTOOLS_ISLICE_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_ISLICE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/itertools/common.hpp"
#include "pythonic/include/__builtin__/xrange.hpp"
#include <iterator>

namespace pythonic
{

  namespace itertools
  {
    template <typename Iterable>
    struct islice_iterator
        : std::iterator<typename Iterable::iterator::iterator_category,
                        typename Iterable::iterator::value_type> {
      typename std::remove_reference<
          typename std::remove_cv<Iterable>::type>::type iterable_ref;
      typename std::remove_reference<
          typename std::remove_cv<Iterable>::type>::type::iterator iterable;

      __builtin__::xrange xr_ref;
      __builtin__::xrange_iterator state;
      __builtin__::xrange_iterator::value_type prev;

      islice_iterator();
      islice_iterator(Iterable const &iterable, __builtin__::xrange const &xr);
      islice_iterator(npos const &n, Iterable const &iterable,
                      __builtin__::xrange const &xr);

      typename Iterable::value_type operator*() const;
      islice_iterator &operator++();
      bool operator==(islice_iterator const &other) const;
      bool operator!=(islice_iterator const &other) const;
      bool operator<(islice_iterator const &other) const;
      int operator-(islice_iterator const &other) const;
    };

    template <typename Iterable>
    struct _islice : islice_iterator<Iterable> {

      using iterator = islice_iterator<Iterable>;
      using value_type = typename Iterable::value_type;

      iterator end_iter;

      _islice();
      _islice(Iterable const &iterable, __builtin__::xrange const &xr);

      iterator &begin();
      iterator const &begin() const;
      iterator end() const;
    };

    template <typename Iterable>
    _islice<typename std::remove_cv<
        typename std::remove_reference<Iterable>::type>::type>
    islice(Iterable &&iterable, long start, long stop, long step = 1);

    template <typename Iterable>
    _islice<typename std::remove_cv<
        typename std::remove_reference<Iterable>::type>::type>
    islice(Iterable &&iterable, long stop);

    DECLARE_FUNCTOR(pythonic::itertools, islice);
  }
}

#endif
