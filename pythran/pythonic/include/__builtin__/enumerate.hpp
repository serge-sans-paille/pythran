#ifndef PYTHONIC_INCLUDE_BUILTIN_ENUMERATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ENUMERATE_HPP

#include "pythonic/include/types/tuple.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <iterator>

namespace pythonic
{

  namespace __builtin__
  {

    namespace details
    {
      // FIXME return value may be a type::make_tuple
      template <class Iterator>
      struct enumerate_iterator
          : public std::iterator<
                typename std::iterator_traits<Iterator>::iterator_category,
                std::tuple<long,
                           typename std::iterator_traits<Iterator>::value_type>,
                ptrdiff_t, std::tuple<long, typename std::iterator_traits<
                                                Iterator>::value_type> *,
                std::tuple<long, typename std::iterator_traits<
                                     Iterator>::value_type> /* not a ref */
                > {
        long value;
        Iterator iter;
        enumerate_iterator();
        enumerate_iterator(Iterator const &iter, long first);
        auto operator*() -> decltype(std::make_tuple(value, *iter));
        enumerate_iterator &operator++();
        enumerate_iterator &operator+=(long n);
        bool operator!=(enumerate_iterator const &other);
        bool operator<(enumerate_iterator const &other);
        long operator-(enumerate_iterator const &other);
      };

      template <class Iterable>
      struct enumerate : enumerate_iterator<typename Iterable::iterator> {
        using iterator = enumerate_iterator<typename Iterable::iterator>;
        // we need to keep one ref over the enumerated sequence alive
        Iterable seq;
        iterator end_iter;

        enumerate();
        enumerate(Iterable seq, long first);
        iterator &begin();
        iterator const &begin() const;
        iterator end() const;
      };
    }

    template <class Iterable>
    details::enumerate<typename std::remove_cv<
        typename std::remove_reference<Iterable>::type>::type>
    enumerate(Iterable &&seq, long first = 0L);

    DECLARE_FUNCTOR(pythonic::__builtin__, enumerate);
  }
}

#endif
