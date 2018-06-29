#ifndef PYTHONIC_INCLUDE_NUMPY_ARANGE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARANGE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class U, class S = long,
            class dtype = types::dtype_t<typename __combined<T, U, S>::type>>
  types::ndarray<typename dtype::type, types::pshape<long>>
  arange(T begin, U end, S step = S(1), dtype d = dtype());

  template <class T>
  types::ndarray<T, types::pshape<long>> arange(T end);

  DECLARE_FUNCTOR(pythonic::numpy, arange);
}
PYTHONIC_NS_END

#endif
