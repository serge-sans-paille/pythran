#ifndef PYTHONIC_NUMPY_NDINDEX_HPP
#define PYTHONIC_NUMPY_NDINDEX_HPP

#include "pythonic/include/numpy/ndindex.hpp"

#include "pythonic/utils/functor.hpp"

#include <numeric>

namespace pythonic
{

  namespace numpy
  {
    template <size_t N>
    ndindex_iterator<N>::ndindex_iterator()
    {
    }

    template <size_t N>
    ndindex_iterator<N>::ndindex_iterator(types::array<long, N> const &shape,
                                          long first)
        : index(first), shape(shape)
    {
    }

    template <size_t N>
    types::array<long, N> ndindex_iterator<N>::operator*()
    {
      types::array<long, N> out;
      long mult = 1;
      for (long j = N - 1; j > 0; j--) {
        out[j] = (index / mult) % shape[j];
        mult *= shape[j];
      }
      out[0] = index / mult;
      return out;
    }

    template <size_t N>
    ndindex_iterator<N> &ndindex_iterator<N>::operator++()
    {
      ++index;
      return *this;
    }

    template <size_t N>
    ndindex_iterator<N> &ndindex_iterator<N>::operator+=(long n)
    {
      index += n;
      return *this;
    }

    template <size_t N>
    bool ndindex_iterator<N>::operator!=(ndindex_iterator<N> const &other)
    {
      return index != other.index;
    }

    template <size_t N>
    bool ndindex_iterator<N>::operator<(ndindex_iterator<N> const &other)
    {
      return index < other.index;
    }

    template <size_t N>
    long ndindex_iterator<N>::operator-(ndindex_iterator<N> const &other)
    {
      return index - other.index;
    }

    template <size_t N>
    _ndindex<N>::_ndindex()
    {
    }

    template <size_t N>
    _ndindex<N>::_ndindex(types::array<long, N> const &shape)
        : ndindex_iterator<N>(shape, 0), shape(shape),
          end_iter(shape, std::accumulate(shape.begin(), shape.end(), 1L,
                                          std::multiplies<long>()))
    {
    }

    template <size_t N>
    typename _ndindex<N>::iterator &_ndindex<N>::begin()
    {
      return *this;
    }

    template <size_t N>
    typename _ndindex<N>::iterator const &_ndindex<N>::begin() const
    {
      return *this;
    }

    template <size_t N>
    typename _ndindex<N>::iterator _ndindex<N>::end() const
    {
      return end_iter;
    }

    template <class... Types>
    _ndindex<sizeof...(Types)> ndindex(Types... args)
    {
      return {types::make_tuple(args...)};
    }

    template <size_t N>
    _ndindex<N> ndindex(types::array<long, N> const &args)
    {
      return {args};
    }

    DEFINE_FUNCTOR(pythonic::numpy, ndindex);
  }
}

#endif
