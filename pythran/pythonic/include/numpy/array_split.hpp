#ifndef PYTHONIC_INCLUDE_NUMPY_ARRAYSPLIT_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARRAYSPLIT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class pS>
  types::list<types::ndarray<T, types::array<long, std::tuple_size<pS>::value>>>
  array_split(types::ndarray<T, pS> const &a, long nb_split);

  template <class T, class pS, class I>
  typename std::enable_if<
      types::is_iterable<I>::value,
      types::list<types::ndarray<
          T, types::array<long, std::tuple_size<pS>::value>>>>::type
  array_split(types::ndarray<T, pS> const &a, I const &split_mask);

  NUMPY_EXPR_TO_NDARRAY0_DECL(array_split);
  DEFINE_FUNCTOR(pythonic::numpy, array_split);
}
PYTHONIC_NS_END

#endif
