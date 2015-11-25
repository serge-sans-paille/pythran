#ifndef PYTHONIC_INCLUDE_NUMPY_ARRAYSPLIT_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARRAYSPLIT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::list<types::ndarray<T, N>> array_split(types::ndarray<T, N> const &a,
                                                  long nb_split);

    template <class T, size_t N, class I>
    typename std::enable_if<types::is_iterable<I>::value,
                            types::list<types::ndarray<T, N>>>::type
    array_split(types::ndarray<T, N> const &a, I const &split_mask);

    NUMPY_EXPR_TO_NDARRAY0_DECL(array_split);
    DECLARE_FUNCTOR(pythonic::numpy, array_split);
  }
}

#endif
