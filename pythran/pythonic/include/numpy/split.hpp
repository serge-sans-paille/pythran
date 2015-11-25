#ifndef PYTHONIC_INCLUDE_NUMPY_SPLIT_HPP
#define PYTHONIC_INCLUDE_NUMPY_SPLIT_HPP

#include "pythonic/include/numpy/array_split.hpp"
#include "pythonic/include/__builtin__/ValueError.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::list<types::ndarray<T, N>> split(types::ndarray<T, N> const &a,
                                            long nb_split);

    template <class T, size_t N, class I>
    typename std::enable_if<types::is_iterable<I>::value,
                            types::list<types::ndarray<T, N>>>::type
    split(types::ndarray<T, N> const &a, I const &split_mask);

    template <class E, class I>
    types::list<types::ndarray<typename E::dtype, E::value>> split(E const &a,
                                                                   I const &);

    DECLARE_FUNCTOR(pythonic::numpy, split);
  }
}

#endif
