#ifndef PYTHONIC_INCLUDE_BUILTIN_XRANGE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_XRANGE_HPP

#include <iterator>

namespace pythonic
{

  namespace __builtin__
  {

    struct xrange_iterator
        : std::iterator<std::random_access_iterator_tag, long, ptrdiff_t,
                        long *, long /*no ref here*/> {
      long value;
      long step;
      long sign;
      xrange_iterator();
      xrange_iterator(long v, long s);
      reference operator*() const;
      xrange_iterator &operator++();
      xrange_iterator operator++(int);
      xrange_iterator &operator+=(long n);
      bool operator!=(xrange_iterator const &other) const;
      bool operator==(xrange_iterator const &other) const;
      bool operator<(xrange_iterator const &other) const;
      long operator-(xrange_iterator const &other) const;
    };

    struct xrange_riterator
        : std::iterator<std::random_access_iterator_tag, long, ptrdiff_t,
                        long *, long /*no ref here*/> {
      long value;
      long step;
      long sign;
      xrange_riterator();
      xrange_riterator(long v, long s);
      long operator*();
      xrange_riterator &operator++();
      xrange_riterator operator++(int);
      xrange_riterator &operator+=(long n);
      bool operator!=(xrange_riterator const &other) const;
      bool operator==(xrange_riterator const &other) const;
      bool operator<(xrange_riterator const &other) const;
      long operator-(xrange_riterator const &other) const;
    };

    struct xrange {
      using value_type = long;
      using iterator = xrange_iterator;
      using const_iterator = xrange_iterator;
      using reverse_iterator = xrange_riterator;
      using const_reverse_iterator = xrange_riterator;

      long _begin;
      long _end;
      long _step;
      long _last;

      void _init_last();
      xrange();
      xrange(long b, long e, long s = 1);
      xrange(long e);
      xrange_iterator begin() const;
      xrange_iterator end() const;
      reverse_iterator rbegin() const;
      reverse_iterator rend() const;
    };

    // clang++ is not happy with PROXY
    namespace functor
    {

      struct xrange {
        template <class... Types>
        pythonic::__builtin__::xrange operator()(Types &&... args);
      };
    }
  }
}

#endif
