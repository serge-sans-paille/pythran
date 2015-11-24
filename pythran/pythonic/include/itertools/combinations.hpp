#ifndef PYTHONIC_INCLUDE_ITERTOOLS_COMBINATIONS_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_COMBINATIONS_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <vector>
#include <iterator>

namespace pythonic
{

  namespace itertools
  {
    namespace details
    {
      template <class T>
      struct combination_iterator
          : std::iterator<std::forward_iterator_tag,
                          types::list<typename T::value_type>, ptrdiff_t,
                          types::list<typename T::value_type> *,
                          types::list<typename T::value_type> /*no ref*/
                          > {
        std::vector<typename T::value_type> pool;
        std::vector<long> indices;
        long r;
        bool stopped;
        types::list<typename T::value_type> result;

        combination_iterator() = default;
        combination_iterator(bool);

        template <class Iter>
        combination_iterator(Iter &&pool, long r);

        types::list<typename T::value_type> operator*() const;
        combination_iterator &operator++();
        bool operator!=(combination_iterator const &other) const;
        bool operator==(combination_iterator const &other) const;
        bool operator<(combination_iterator const &other) const;
      };

      template <class T>
      struct combination : combination_iterator<T> {
        using iterator = combination_iterator<T>;
        using value_type = T;

        long num_elts;

        combination() = default;

        template <class Iter>
        combination(Iter &&iter, long elts);
        iterator const &begin() const;
        iterator begin();
        iterator end() const;
      };
    }

    template <typename T0>
    details::combination<
        typename std::remove_cv<typename std::remove_reference<T0>::type>::type>
    combinations(T0 &&iter, long num_elts);

    DECLARE_FUNCTOR(pythonic::itertools, combinations);
  }
}

#endif
