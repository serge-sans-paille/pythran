#ifndef PYTHONIC_NUMPY_COPYTO_HPP
#define PYTHONIC_NUMPY_COPYTO_HPP

#include "pythonic/include/numpy/copyto.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  template <class T, class pS0, class pS1>
  types::ndarray<T, pS0> copyto(types::ndarray<T, pS0> &out,
                                types::ndarray<T, pS1> const &a)
  {
    std::copy(a.fbegin(), a.fend(), out.fbegin());
    return out;
  }
  template <class T, class pS, class E>
  types::ndarray<T, pS> copyto(types::ndarray<T, pS> &out,
                                E const &expr)
  {
    out.initialize_from_expr(expr);
    return out;
  }
}
PYTHONIC_NS_END

#endif
