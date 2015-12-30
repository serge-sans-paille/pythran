#ifndef PYTHONIC_BUILTIN_ENUMERATE_HPP
#define PYTHONIC_BUILTIN_ENUMERATE_HPP

#include "pythonic/include/__builtin__/enumerate.hpp"

#include "pythonic/utils/functor.hpp"

#include <tuple>

namespace pythonic
{

  namespace __builtin__
  {

    namespace details
    {
      /// enumerate_iterator implementation

      template <class Iterator>
      enumerate_iterator<Iterator>::enumerate_iterator()
      {
      }

      template <class Iterator>
      enumerate_iterator<Iterator>::enumerate_iterator(Iterator const &iter,
                                                       long first)
          : value(first), iter(iter)
      {
      }

      template <class Iterator>
      typename enumerate_iterator_base<Iterator>::value_type
          enumerate_iterator<Iterator>::
          operator*()
      {
        return std::make_tuple(value, *iter);
      }

      template <class Iterator>
      typename enumerate_iterator<Iterator>::enumerate_iterator &
          enumerate_iterator<Iterator>::
          operator++()
      {
        ++value, ++iter;
        return *this;
      }

      template <class Iterator>
      typename enumerate_iterator<Iterator>::enumerate_iterator &
          enumerate_iterator<Iterator>::
          operator+=(long n)
      {
        value += n, iter += n;
        return *this;
      }

      template <class Iterator>
      bool enumerate_iterator<Iterator>::operator!=(typename enumerate_iterator<
          Iterator>::enumerate_iterator const &other)
      {
        return iter != other.iter;
      }

      template <class Iterator>
      bool enumerate_iterator<Iterator>::operator<(typename enumerate_iterator<
          Iterator>::enumerate_iterator const &other)
      {
        return iter < other.iter;
      }

      template <class Iterator>
      long enumerate_iterator<Iterator>::operator-(typename enumerate_iterator<
          Iterator>::enumerate_iterator const &other)
      {
        return iter - other.iter;
      }

      /// details::enumerate implementation
      template <class Iterable>
      enumerate<Iterable>::enumerate()
      {
      }

      template <class Iterable>
      enumerate<Iterable>::enumerate(Iterable seq, long first)
          : Iterable(seq), iterator(Iterable::begin(), first),
            end_iter(Iterable::end(), -1)
      {
      }

      template <class Iterable>
      typename enumerate<Iterable>::iterator &enumerate<Iterable>::begin()
      {
        return *this;
      }

      template <class Iterable>
      typename enumerate<Iterable>::iterator const &
      enumerate<Iterable>::begin() const
      {
        return *this;
      }

      template <class Iterable>
      typename enumerate<Iterable>::iterator enumerate<Iterable>::end() const
      {
        return end_iter;
      }
    }

    /// enumerate implementation

    template <class Iterable>
    details::enumerate<typename std::remove_cv<
        typename std::remove_reference<Iterable>::type>::type>
    enumerate(Iterable &&seq, long first)
    {
      return {std::forward<Iterable>(seq), first};
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, enumerate);
  }
}

#endif
