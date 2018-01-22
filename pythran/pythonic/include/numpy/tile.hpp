#ifndef PYTHONIC_INCLUDE_NUMPY_TILE_HPP
#define PYTHONIC_INCLUDE_NUMPY_TILE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E>
  types::ndarray<typename E::dtype, E::value> tile(E const &expr, int reps);

  template <class E, size_t N>
  types::ndarray<typename E::dtype, N> tile(E const &expr,
                                            types::array<long, N> const &reps);

  DECLARE_FUNCTOR(pythonic::numpy, tile);
}
PYTHONIC_NS_END

#endif
