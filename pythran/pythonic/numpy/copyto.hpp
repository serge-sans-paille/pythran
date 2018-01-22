#ifndef PYTHONIC_NUMPY_COPYTO_HPP
#define PYTHONIC_NUMPY_COPYTO_HPP

#include "pythonic/include/numpy/copyto.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  template <class T, size_t N>
  types::ndarray<T, N> copyto(types::ndarray<T, N> &out,
                              types::ndarray<T, N> const &a)
  {
    std::copy(a.fbegin(), a.fend(), out.fbegin());
    return out;
  }

  DEFINE_FUNCTOR(pythonic::numpy, copyto);
}
PYTHONIC_NS_END

#endif
