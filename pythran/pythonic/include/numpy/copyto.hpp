#ifndef PYTHONIC_INCLUDE_NUMPY_COPYTO_HPP
#define PYTHONIC_INCLUDE_NUMPY_COPYTO_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  template <class T, class pS0, class pS1>
  types::ndarray<T, pS0> copyto(types::ndarray<T, pS0> &out,
                                types::ndarray<T, pS1> const &a);

  DEFINE_FUNCTOR(pythonic::numpy, copyto);
}
PYTHONIC_NS_END

#endif
