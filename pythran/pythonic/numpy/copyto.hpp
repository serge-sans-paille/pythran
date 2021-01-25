#ifndef PYTHONIC_NUMPY_COPYTO_HPP
#define PYTHONIC_NUMPY_COPYTO_HPP

#include "pythonic/include/numpy/copyto.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  template <class T, class pS, class E>
  types::ndarray<T, pS> copyto(types::ndarray<T, pS> &out, E const &expr)
  {
    out[types::contiguous_slice(0, types::none_type{})] = expr;
    return out;
  }
}
PYTHONIC_NS_END

#endif
