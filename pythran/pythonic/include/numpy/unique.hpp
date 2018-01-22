#ifndef PYTHONIC_INCLUDE_NUMPY_UNIQUE_HPP
#define PYTHONIC_INCLUDE_NUMPY_UNIQUE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/tuple.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E>
  types::ndarray<typename E::dtype, 1> unique(E const &expr);

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, 1>, types::ndarray<long, 1>>
  unique(E const &expr, bool return_index);

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, 1>, types::ndarray<long, 1>,
             types::ndarray<long, 1>>
  unique(E const &expr, bool return_index, bool return_inverse);

  DECLARE_FUNCTOR(pythonic::numpy, unique)
}
PYTHONIC_NS_END

#endif
