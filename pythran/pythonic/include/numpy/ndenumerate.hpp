#ifndef PYTHONIC_INCLUDE_NUMPY_NDENUMERATE_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDENUMERATE_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E>
  struct ndenumerate_iterator {
    using iterator_category = std::random_access_iterator_tag;
    using value_type = std::tuple<types::array_tuple<long, E::value>, typename E::dtype>;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type /* no ref */;

    long index;
    E const &expr;
    typename E::dtype *iter;

    ndenumerate_iterator();
    ndenumerate_iterator(E const &expr, long first);

    value_type operator*() const;

    ndenumerate_iterator &operator++();
    ndenumerate_iterator &operator+=(long n);
    bool operator!=(ndenumerate_iterator const &other) const;
    bool operator==(ndenumerate_iterator const &other) const
    {
      return !(*this != other);
    }
    bool operator<(ndenumerate_iterator const &other) const;
    long operator-(ndenumerate_iterator const &other) const;
  };

  template <class E>
  struct _ndenumerate : ndenumerate_iterator<E> {
    using iterator = ndenumerate_iterator<E>;
    E expr; // we need to keep one ref over the enumerated sequence alive
    iterator end_iter;

    _ndenumerate();
    _ndenumerate(E const &expr);
    iterator &begin();
    iterator const &begin() const;
    iterator end() const;
  };

  template <class T, class pS>
  _ndenumerate<types::ndarray<T, pS>> ndenumerate(types::ndarray<T, pS> const &expr);

  NUMPY_EXPR_TO_NDARRAY0_DECL(ndenumerate);
  DEFINE_FUNCTOR(pythonic::numpy, ndenumerate);
} // namespace numpy
PYTHONIC_NS_END

#endif
