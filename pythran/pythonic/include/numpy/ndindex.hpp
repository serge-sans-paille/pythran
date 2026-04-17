#ifndef PYTHONIC_INCLUDE_NUMPY_NDINDEX_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDINDEX_HPP

#include "pythonic/include/types/tuple.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <size_t N>
  struct ndindex_iterator {
    using iterator_category = std::random_access_iterator_tag;
    using value_type = types::array_tuple<long, N>;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type /* no ref */;

    long index;
    types::array_tuple<long, N> shape;
    ndindex_iterator() = default;
    ndindex_iterator(types::array_tuple<long, N> const &shape, long first);
    value_type operator*() const;
    ndindex_iterator &operator++();
    ndindex_iterator &operator+=(long n);
    bool operator!=(ndindex_iterator const &other) const;
    bool operator==(ndindex_iterator const &other) const
    {
      return !(*this != other);
    }
    bool operator<(ndindex_iterator const &other) const;
    long operator-(ndindex_iterator const &other) const;
  };

  template <size_t N>
  struct _ndindex : ndindex_iterator<N> {
    using iterator = ndindex_iterator<N>;
    types::array_tuple<long, N> shape;
    iterator end_iter;

    _ndindex() = default;
    _ndindex(types::array_tuple<long, N> const &shape);
    iterator &begin();
    iterator const &begin() const;
    iterator end() const;
  };

  template <class... Types>
  _ndindex<sizeof...(Types)> ndindex(Types... args);

  template <size_t N>
  _ndindex<N> ndindex(types::array_tuple<long, N> const &args);

  template <class... Tys>
  _ndindex<sizeof...(Tys)> ndindex(types::pshape<Tys...> const &args);

  DEFINE_FUNCTOR(pythonic::numpy, ndindex);
} // namespace numpy
PYTHONIC_NS_END

#endif
