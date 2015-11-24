#ifndef PYTHONIC_INCLUDE_NUMPY_NDINDEX_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDINDEX_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/tuple.hpp"

#include <numeric>

namespace pythonic
{

  namespace numpy
  {
    template <size_t N>
    struct ndindex_iterator
        : std::iterator<
              std::random_access_iterator_tag, types::array<long, N>, ptrdiff_t,
              types::array<long, N> *,
              types::array<
                  long, N> /* reference_type, but no reference is possible*/> {
      long index;
      types::array<long, N> shape;
      ndindex_iterator();
      ndindex_iterator(types::array<long, N> const &shape, long first);
      types::array<long, N> operator*();
      ndindex_iterator &operator++();
      ndindex_iterator &operator+=(long n);
      bool operator!=(ndindex_iterator const &other);
      bool operator<(ndindex_iterator const &other);
      long operator-(ndindex_iterator const &other);
    };

    template <size_t N>
    struct _ndindex : ndindex_iterator<N> {
      using iterator = ndindex_iterator<N>;
      types::array<long, N> shape;
      iterator end_iter;

      _ndindex();
      _ndindex(types::array<long, N> const &shape);
      iterator &begin();
      iterator const &begin() const;
      iterator end() const;
    };

    template <class... Types>
    _ndindex<sizeof...(Types)> ndindex(Types... args);

    template <size_t N>
    _ndindex<N> ndindex(types::array<long, N> const &args);

    DECLARE_FUNCTOR(pythonic::numpy, ndindex);
  }
}

#endif
