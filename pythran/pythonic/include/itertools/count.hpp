#ifndef PYTHONIC_INCLUDE_ITERTOOLS_COUNT_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_COUNT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/combined.hpp"

#include <iterator>

namespace pythonic
{

  namespace itertools
  {
    namespace details
    {
      template <class T>
      struct count_iterator
          : std::iterator<std::random_access_iterator_tag, T> {
        T value;
        T step;
        count_iterator() = default;
        count_iterator(T value, T step);
        T operator*() const;
        count_iterator &operator++();
        count_iterator &operator+=(long n);
        bool operator!=(count_iterator const &other) const;
        bool operator==(count_iterator const &other) const;
        bool operator<(count_iterator const &other) const;
        long operator-(count_iterator const &other) const;
      };

      template <class T>
      struct count : count_iterator<T> {
        using value_type = T;
        using iterator = count_iterator<T>;

        count() = default;
        count(T value, T step);
        iterator &begin();
        iterator const &begin() const;
        iterator end() const;
      };
    }

    template <typename T0, typename T1 = T0>
    details::count<typename __combined<T0, T1>::type> count(T0 start,
                                                            T1 step = 1);

    details::count<long> count();

    DECLARE_FUNCTOR(pythonic::itertools, count);
  }
}

#endif
