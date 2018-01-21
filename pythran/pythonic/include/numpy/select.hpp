#ifndef PYTHONIC_INCLUDE_NUMPY_SELECT_HPP
#define PYTHONIC_INCLUDE_NUMPY_SELECT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/int_.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <class T, class U>
  types::ndarray<typename U::dtype, U::value>
  select(types::list<T> const &condlist, types::list<U> const &choicelist,
         typename U::dtype _default = 0);

  template <class T, size_t N, class U>
  types::ndarray<T, N>
  select(types::list<types::ndarray<U, N>> const &condlist,
         types::list<types::ndarray<T, N>> const &choicelist, T _default = 0);

  DECLARE_FUNCTOR(pythonic::numpy, select);
}
PYTHONIC_NS_END

#endif
