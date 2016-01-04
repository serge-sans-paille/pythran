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
      using enumerate_iterator_base = std::iterator<
          typename std::iterator_traits<Iterator>::iterator_category,
          std::tuple<long,
                     typename std::iterator_traits<Iterator>::value_type>>;

      template <class Iterator>
      struct enumerate_iterator : public enumerate_iterator_base<Iterator> {
        long value;
        Iterator iter;
        enumerate_iterator();
        enumerate_iterator(Iterator const &iter, long first);
        typename enumerate_iterator_base<Iterator>::value_type operator*();
        enumerate_iterator &operator++();
        enumerate_iterator &operator+=(long n);
        bool operator!=(enumerate_iterator const &other);
        bool operator<(enumerate_iterator const &other);
        long operator-(enumerate_iterator const &other);
      };

      template <class Iterable>
      struct enumerate
          : private Iterable, /* to hold a reference on the iterable */
            public enumerate_iterator<
                typename Iterable::iterator> /* to be compatible with
                                                __builtin__.next*/
            {
        using iterator = enumerate_iterator<typename Iterable::iterator>;
        using iterator::operator*;
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
